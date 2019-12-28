from distutils.core import setup, Extension
import os

def main():
    setup(name="cool",
          version="1.0.0",
          description="Python PiNAT library",
          author="Ofri Marx & Elad Matia",
          author_email="ofrikm@gmail.com",
          ext_modules=[Extension("pynat", ["src/cpp/pynat.cpp", "src/cpp/pySniffer.cpp", "src/cpp/sniffer.cpp", "src/cpp/packetPool.cpp", "src/cpp/coreFunctions.cpp", "src/cpp/packet.cpp"], extra_compile_args=["-Wno-unused", "-Iexternals"], extra_link_args=["-Lexternals", "-ltins"])])

if __name__ == "__main__":
    main()