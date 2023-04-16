FROM ghcr.io/spezifisch/hise-builder:main

COPY . /root/Reach/
WORKDIR /root/Reach

RUN ./Packaging/GNU/compileAndBuild.sh
