#!/usr/bin/echo Do not invoke directly.
##===============================================================================n
## @file client.py
## @brief Client for REST API Services
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install folder
from ..http import HTTPClient, HTTPTarget
import json

class RESTClient (HTTPClient):
    messaging_flavor = 'REST'

    # `service_name` should be overwritten by final subclass to look up settings
    # for this endpoint (e.g., host/port, ...).
    service_name = None

    def get_json(self, rel_url, kwargs={}, headers={}):
        string_args = { key : json.dumps(value)
                        for (key, value) in kwargs.items() }

        response = self.get(rel_url, string_args, headers, 'application/json')
        return json.loads(response.read())

