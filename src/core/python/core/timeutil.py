#!/usr/bin/echo Do not invoke directly.
#===============================================================================
## @file timeutil.py
## @brief Miscellaneous date/time utilities
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install folder
from picarro.core.invocation import safe_invoke, check_type

import time

### Standardized time string
def isotime(timestamp : float = None,
            delimiter=" ",          # Separator between date and time strings
            decimals=3,             # Decimal places
            local=True,             # Produce local time as opposed to UTC
            with_zone_offset=False, # Append ISO timezone offset, e.g. "-0800"
            with_zone_name=False):  # Append non-standard zone name, e.g. "PST"


    if timestamp is None:
        timestamp = time.time()

    timestruct = time.localtime(timestamp) if local else time.gmtime(timestamp)
    parts = [ time.strftime(f"%F{delimiter}%T", timestruct) ]

    if decimals:
        fraction = timestamp - int(timestamp)
        parts.append(".%0*d"%(decimals, (10**decimals) * fraction))

    if with_zone_name:
        if local:
            parts.extend([" ", time.tzname[ts.tm_isdst]])
        else:
            parts.append(" UTC")

    elif with_zone_offset:
        if local:
            parts.append(
                "%+03d%02d"%(-time.timezone / 3600,
                             (-time.timezone % 3600) / 60))
        else:
            parts.append("Z")

    return "".join(parts)


def jsontime(timestamp : float = None):
    return isotime(timestamp, delimiter="T", decimals=3, local=False, with_zone_offset=True)
