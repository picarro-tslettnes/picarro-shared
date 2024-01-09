#!/usr/bin/python3
#===============================================================================
## @file settingsstore.py
## @brief Obtain settings from JSON file(s)
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

from jsonreader import JsonReader
from paths      import normalizedSearchPath, settingsPath, FilePath, SearchPath
from typing     import Sequence, Optional
import os
import os.path
import sys
import platform
import re

FilePath   = str
SearchPath = Sequence[FilePath]


class SettingsStore (JsonReader):
    '''A specialized dictionary containing configuration settings, loaded from one
    or more JSON file(s) located within specific settings folders.

    Any script-style or C++-style comments (prefixed with either `#` or `//`)
    are strippped off before parsing.

    See `__init__()` for a description of how settings folder(s) are determined.
    '''

    def __init__(self,
                 filenames  : [FilePath, SearchPath] = [],
                 searchpath : SearchPath = settingsPath()):
        '''Initialize a new SettingsStore instance from the specified JSON file(s).
        Any script-style or C++-style comments (prefixed with either `#` or `//`)
        are strippped off before parsing.

        @param[in] filenames
           A single JSON file or a list of JSON files from which to load initial
           settings.  If a `.json` suffix is missing, it is added.

        @param[in] searchpath
           A list of directories in which to look for relative filenames. Each
           directory name may be absolute or relative. In the latter case, an
           upward search for that (dominating) folder name starts at the
           installation folder where this module is located, and ends at the
           root of the filesystem.

        If `searchpath` is not not provided, it is obtained from the environment
        variable `CONFIGPATH`, where folder names are presumed to be separated
        by the OS-specific path separator (`:` on UNIX, `;` on Windows).

        Lastly, if `CONFIGPATH` is not defined, the default search path comprises:
        * a per-unit configuration folder (`/etc/picarro` on UNIX or `C:/Cc` on Windows)
        * an application-provided default settings folder (`share/settings`), presumed
          relative to the top-level folder where the software is installed.

        For example, consider a deployment where this module is located somewhere
        inside `/opt/picarro/python/`, and default configurations are stored in JSON
        files within the folder `/opt/picarro/share/settings/`.  Now let's say you
        create a SettingsStore instance as follows:

        ```
        my_settings = SettingsStore(
                          filenames = ['my_settings.json', 'factory_settings.json']),
                          searchpath = ['/etc/picarro', 'share/settings'])
        ```

        Since `searchpath` is not explicitly provided, the default value
        `['/etc/picarro', 'share/settings']` is used.  Settings are then loaded
        and merged in from whichever of the following paths exist, in turn:

        1. `/etc/picarro/my_settings.json`
        2. `/opt/picarro/share/settings/my_settings.json`
        3. `/etc/picarro/factory_settings.json`
        4. `/opt/picarro/share/settings/factory_settings.json`

        See also `load_settings()`.

        '''

        self.searchpath = searchpath
        super().__init__(filenames)


    def load_settings(self,
                      filename   : FilePath,
                      searchpath : Optional[SearchPath] = None):

        '''Load in settings from the specified file.

        @param[in] filename
            Settings file to load. The name may be absolute or relative,
            see `__init__()` for details.

        Any comments starting with `#` or `//` until the end of the line are
        stripped away prior to JSON parsing.
        '''

        if searchpath:
            search = normalizedSearchPath(searchpath)
        else:
            search = self.searchpath

        for filepath in self._settingsFilePaths(filename, search):
            super().load_settings(filepath)


    @classmethod
    def _settingsFilePaths(cls,
                           basename : FilePath,
                           searchpath):
        stem, ext = os.path.splitext(basename)
        if not ext:
            basename += ".json"

        filepaths = []

        if os.path.isabs(basename):
            filepaths.append(basename)
        else:
            for folder in searchpath:
                filepath = os.path.join(folder, basename)
                if os.path.isfile(filepath):
                    filepaths.append(filepath)

        return filepaths
