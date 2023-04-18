FROM ghcr.io/spezifisch/hise-builder:main-hise-3.0.3-ci-dsp

ARG PLUGIN_VERSION="v1.5.0"
ARG VST3_BUNDLE="Reach-$PLUGIN_VERSION-Linux-VST3.tar.gz"

COPY . /root/Reach/

# compile plugin
WORKDIR /root/Reach
RUN xvfb-run ./Packaging/GNU/compileAndBuild.sh

# bundle plugin
WORKDIR /root/Reach/Binaries/Builds/LinuxMakefile/build
RUN mkdir -p /output \
    && tar cfvz "/output/$VST3_BUNDLE" Reach.vst3 \
    && find /output -type f -exec sha256sum '{}' \;
