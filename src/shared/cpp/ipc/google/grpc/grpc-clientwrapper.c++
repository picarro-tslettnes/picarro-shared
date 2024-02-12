/// -*- c++ -*-
//==============================================================================
/// @file grpc-clientwrapper.c++
/// @brief Client-side wrapper functionality for Picarro gRPC services
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "grpc-clientwrapper.h++"

namespace shared::grpc
{
    ClientWrapperBase::ClientWrapperBase(
        const std::string &full_service_name,
        const std::string &host,
        bool wait_for_ready,
        const std::shared_ptr<::grpc::ChannelCredentials> &creds)
        : Base("gRPC Client", full_service_name),
          host_(this->realaddress(host,
                                  HOST_OPTION,
                                  PORT_OPTION,
                                  "localhost",
                                  8080)),
          wait_for_ready(wait_for_ready),
          channel(this->create_channel(creds))
    {
    }

    std::shared_ptr<::grpc::ChannelInterface> ClientWrapperBase::create_channel(
        const std::shared_ptr<::grpc::ChannelCredentials> &creds) const
    {
        uint max_send_size = this->max_request_size();
        uint max_recv_size = this->max_reply_size();
        ::grpc::ChannelArguments args;

        if (max_send_size)
        {
            args.SetMaxSendMessageSize(max_send_size);
        }
        if (max_recv_size)
        {
            args.SetMaxReceiveMessageSize(max_recv_size);
        }

        if (max_send_size || max_recv_size)
        {
            logf_debug(
                "%s creating custom channel to %s, max_send_size=%d, max_receive_size=%d",
                *this,
                this->host(),
                max_send_size,
                max_recv_size);
            return ::grpc::CreateCustomChannel(this->host(), creds, args);
        }
        else
        {
            logf_debug(
                "%s creating standard channel to %s",
                *this,
                this->host());
            return ::grpc::CreateChannel(this->host(), creds);
        }
    }

    std::string ClientWrapperBase::host() const
    {
        return this->host_;
    }

    void ClientWrapperBase::check(const ::grpc::Status &status) const
    {
        if (!status.ok())
        {
            Status(status).throw_if_error();
        }
    }

    void ClientWrapperBase::check(const Status &status) const
    {
        status.throw_if_error();
    }

    bool ClientWrapperBase::get_wait_for_ready()
    {
        return this->wait_for_ready;
    }

    void ClientWrapperBase::set_wait_for_ready(bool wait_for_ready)
    {
        this->wait_for_ready = wait_for_ready;
    }

    void ClientWrapperBase::set_request_timeout(std::optional<dt::Duration> timeout)
    {
        this->request_timeout = timeout;
    }

    bool ClientWrapperBase::available(const dt::Duration &timeout) const
    {
        dt::TimePoint deadline = dt::Clock::now() + timeout;
        grpc_connectivity_state state = this->channel->GetState(true);

        while (((state == GRPC_CHANNEL_IDLE) || (state == GRPC_CHANNEL_CONNECTING)) &&
               this->channel->WaitForStateChange(state, deadline))
        {
            state = this->channel->GetState(true);
        }
        return (state == GRPC_CHANNEL_READY);
    }
}  // namespace shared::grpc
