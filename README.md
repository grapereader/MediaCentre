##ViaWare Media Centre - Suite of programs for rpi-based HTPC

###Building

Required Libraries:
* MySQL++
* Crypto++
* Boost libraries
  * System
  * Filesystem
  * ASIO
* glib 2.0 (for GIO)

Run configure.py to generate Makefiles for all subprojects.
Then, 'make all' in the root directory.

The frontend requires NodeJS and npm.
Enter ctrl-frontend directory, run 'npm install' and 'npm run-script build'

###License

Licensed under GPL v3

