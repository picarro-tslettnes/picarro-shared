/// -*- c++ -*-
//==============================================================================
/// @file zmq-protobuf-server.c++
/// @brief RPC functionalty over ZeroMQ using ProtoBuf - server
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "zmq-protobuf-server.h++"
#include "protobuf-event-types.h++"
#include "platform/path.h++"
#include "logging/logging.h++"

namespace picarro::zmq
{
    ProtoBufServer::ProtoBufServer(const std::string &bind_address,
                                   const std::string &channel_name,
                                   RequestHandlerMap &&handler_map)
        : Super(bind_address, channel_name),
          handler_map(std::move(handler_map))
    {
    }

    void ProtoBufServer::initialize()
    {
        Super::initialize();
        for (const auto &[interface_name, handler]: this->handler_map)
        {
            handler->initialize();
        }
    }

    void ProtoBufServer::deinitialize()
    {
        for (const auto &[interface_name, handler]: this->handler_map)
        {
            handler->deinitialize();
        }
        Super::deinitialize();
    }

    void ProtoBufServer::process_binary_request(const types::ByteArray &packed_request,
                                                types::ByteArray *packed_reply)
    {
        Picarro::RR::Request request;
        Picarro::RR::Reply reply;

        logf_debug("Received binary request: %s", packed_request);

        if (request.ParseFromArray(packed_request.data(), packed_request.size()))
        {
            this->process_protobuf_request(request, &reply);
        }
        else
        {
            this->insert_error_response(
                &reply,
                Picarro::RR::STATUS_INVALID,
                "Failed to deserialize ProtoBuf request",
                picarro::status::Flow::CANCELLED,
                {{"channel", this->channel_name()},
                 {"payload", packed_request.to_hex(true, 4)}});
        }

        protobuf::to_bytes(reply, packed_reply);
    }

    void ProtoBufServer::process_protobuf_request(const Picarro::RR::Request &request,
                                                   Picarro::RR::Reply *reply)
    {
        if (RequestHandlerPtr handler = this->handler_map.get(request.interface_name()))
        {
            return handler->process_method_request(request, reply);
        }
        else
        {
            return this->insert_error_response(
                reply,
                Picarro::RR::STATUS_INVALID,
                "No such interface",
                picarro::status::Flow::CANCELLED,
                {{"channel", this->channel_name()},
                 {"interface", request.interface_name()}});
        }
    }

    void ProtoBufServer::insert_error_response(Picarro::RR::Reply *reply,
                                               Picarro::RR::StatusCode status_code,
                                               const std::string &text,
                                               picarro::status::Flow flow,
                                               const types::KeyValueMap &attributes)
    {
        Picarro::RR::Status *status = reply->mutable_status();
        status->set_code(status_code);

        status::Event event(text,
                            picarro::status::Domain::APPLICATION,
                            platform::path->exec_name(),
                            static_cast<status::Event::Code>(status_code),
                            Picarro::RR::StatusCode_Name(status_code),
                            picarro::status::Level::FAILED,
                            flow,
                            {},
                            attributes);

        protobuf::encode(event, status->mutable_details());
    }

}  // namespace picarro::zmq
