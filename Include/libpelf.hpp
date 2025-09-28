#ifndef PELF_LIBPELF_HPP
#define PELF_LIBPELF_HPP

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <filesystem>
#include <chrono>
#include <array>

#include "libpelf_system.hpp"

struct PELF_Handle;

enum PELF_Version {
    PELF_V1_0
};

enum PELF_Architecture {
    X86_64,
    ARM64,
    RISCV64
};

enum PELF_SignatureType {
    X509,
    PKCS12
};

struct PELF_SigCert {
    std::string issuer;
    std::string subject;
    std::array<uint8_t, 32> fingerprint;
    std::vector<uint8_t> serial;
    std::chrono::system_clock::time_point notBefore;
    std::chrono::system_clock::time_point notAfter;
    std::vector<uint8_t> data;
    bool is_certificateAuthority = false;
};

struct PELF_Signature {
    std::vector<uint8_t> sigBlob;
    PELF_SignatureType sigType;
    std::vector<PELF_SigCert> certChain;
    bool fullVerification = false;
    std::optional<std::string> signer;
    std::optional<std::string> verificationError;
};

struct PELF_Manifest {
    std::string packageName;
    std::string displayAppName;
    std::string appName;
    std::string appVersion;
    int appVersionCode;
};

struct PELF_LibraryInfo {
    bool internal;
    bool loaded;
    std::string filename;
    std::string name;
};

bool PELF_valid(const std::filesystem::path& path);

std::unique_ptr<PELF_Handle> PELF_open(const std::string& path);
std::unique_ptr<PELF_Handle> PELF_open(const void* data, size_t size);

std::vector<std::string> PELF_listResources(const PELF_Handle* handle);
std::optional<std::vector<uint8_t>> PELF_getResource(const PELF_Handle* handle, const std::string& resource_path);

std::vector<PELF_LibraryInfo> PELF_listLibraries(const PELF_Handle* handle);
std::optional<std::vector<uint8_t>> PELF_getLibrary(const PELF_Handle* handle, const std::string& libName);

std::vector<PELF_Signature> PELF_getExecCertificate(const PELF_Handle* handle);
bool PELF_verifySignature(const PELF_Handle* handle);
bool PELF_verifySignature(const PELF_Handle* handle, const std::vector<std::filesystem::path>& caPaths);
bool PELF_verifySignature(const PELF_Handle* handle, const std::string& caDirPath);

PELF_Manifest PELF_getManifest(const PELF_Handle* handle);

std::vector<PELF_Architecture> PELF_allowedArchitectures(const PELF_Handle* handle);

PELF_Version PELF_binVersion(const PELF_Handle* handle);

#endif //PELF_LIBPELF_HPP