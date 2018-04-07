from conans import ConanFile

class ShivaConan(ConanFile):
    name = "shiva"
    version = "1.0.0"
    license = "https://www.apache.org/licenses/LICENSE-2.0"
    url = "https://github.com/tuncb/shiva"
    description = ("A c++ wrapper around mpi")

    def package(self):
        self.copy("*", dst="shiva", src="../projects/shiva/include/shiva")
    def package_info(self):
        self.cpp_info.includedirs = ['.']
