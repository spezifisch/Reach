FROM ghcr.io/spezifisch/hise-builder@sha256:a92fcd485d1653720c0a1920e018f06f6673e39830093cadaaa14ccaa4ef5eec

ARG REACH_VERSION=1.5.0
ARG VST3_BUNDLE=Reach-$REACH_VERSION-VST3.tar.xz

COPY . /root/Reach/

# Fix compiler error. Not sure if I'm using HISE wrong or if this is a bug on their end
RUN cd HISE && patch -p1 -i ../Reach/HISE/node-include.diff

# compile plugin
WORKDIR /root/Reach
RUN ./Packaging/GNU/compileAndBuild.sh

# bundle VST3
WORKDIR /root/Reach/Binaries/Builds/LinuxMakefile/build
RUN tar cfvz /output/$VST3_BUNDLE Reach.vst3 \
    && ls -lh /output/$VST3_BUNDLE
