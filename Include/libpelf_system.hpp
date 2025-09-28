// Please note that PELF will be used by AnlinxOS itself, which accesses both Desktop and Mobile systems
// oh, and yes, I am taking heavy inspiration from the Android Runtime Permission System itself.

#ifndef PELF_LIBPELF_PERMISSIONS_HPP
#define PELF_LIBPELF_PERMISSIONS_HPP

#include <string>

enum PELF_PermissionLabel {
    ACCESS_FILESYSTEM,       // Applies permissions to ACCESS_MEDIA_FILES and similar, once granted or denied
    ACCESS_REGISTRY,

    MOUNT_FILESYSTEMS,
    UNMOUNT_FILESYSTEMS,
    FORMAT_FILESYSTEMS,

    ACCESS_MEDIA_FILES,     // << Allows access only to "Pictures", "Videos", "Music" and "DCIM"
    ACCESS_DOWNLOAD_FILES,  // << Allows access only to "Download(s)"
    ACCESS_DOCUMENT_FILES,  // << Allows access only to "Documents"
    ACCESS_TEMPLATE_FILES,  // << Allows access only to "Templates" (template files for file creations)

    START_PROCESSES,
    START_PROCESSES_SUPERUSER, // << Allows a program to run processes as system / root
    TRACE_PROCESSES,           // << Allows a process to trace system calls
    MANAGE_PROCESSES,          // << Allows a process to read and write process info
    LIST_PROCESSES,            // << Allows a process to list all running processes
    KILL_PROCESSES,            // << Allows a process to send signals to processes (e.g. SIGKILL)

    ACCESS_PROFILE_DATA,      // << allows read and write access to user info outside the current profile
    ACCESS_PROFILE_FILES,     // << allows read and write access to user home directory outside the current profile
    INTERACT_ACROSS_PROFILES, // << allows access to other profiles outside the current running profile
    ACCESS_CLIPBOARD,         // << allows read and write access to the clipboard
    ACCESS_DESKTOP,           // << allows access to Desktop itself, along with wallpaper access and installing shortcuts

    INTERNET,              // << Allows the process to perform network connections
    MANAGE_NETWORK_STATE,  // << Allows the process to access network interfaces and their states
    BIND_NETWORK_STATE,    // << Allows for services, such as VPNs, to rely on this permission

    BLUETOOTH,
    BLUETOOTH_ADMIN,
    BLUETOOTH_ADVERTISE,
    BLUETOOTH_CONNECT,
    BLUETOOTH_SCAN,

    ACCESS_CAMERA_DEVICES,      // << Read / Write access to camera devices, along with creation of virtual cameras
    ACCESS_AUDIO_DEVICES,       // << Read / Playback access to audio devices
    ACCESS_USB_DEVICES,         // << Read / Write access to external USB devices (if kernel module is not present for a specific device)
    ACCESS_INPUT_DEVICES,       // << Read / Write access to input devices (e.g. keyboard, mouse)
    ACCESS_OUTPUT_DEVICES,      // << Read / Write access to output devices (e.g. GPUs, monitors, screens, cameras)
    ACCESS_SENSORS,             // << Access to regular sensors (e.g. Accelerator, Gyroscope)
    ACCESS_BODY_SENSORS,        // << Separate from regular sensors (Accelerator), this allows to access sensors to a human body (e.g. heart beat)
    ACCESS_NFC_DEVICES,         // << Allows access to Near-Field Communication devices
    ACCESS_BIOMETRIC_DEVICES,   // << Allows access to devices like the IR and fingerprint sensors
    FIND_NEARBY_DEVICES,

    ACCESS_PRECISE_LOCATION,   // << GPS location
    ACCESS_AVERAGE_LOCATION,   // << IP-based location

    KERNEL_ACCESS,           // << allows the retrieval of the kernel status (loaded modules, version)
    KERNEL_LOAD_MODULES,     // << perform load_module call
    KERNEL_REMOVE_MODULES,   // << perform unload_module call
    KERNEL_ADD_MODULES,      // << adds additional kernel modules
    KERNEL_DELETE_MODULES,   // << removes kernel modules from the system

    ACCESS_IPC,
    ACCESS_IPC_MEMORY,
    ACCESS_IPC_PIPES,
    ACCESS_IPC_SOCKETS,
    ACCESS_IPC_CROSS_USERS_HIGHER, // << Allows processes to communicate with higher users (e.g. system/root)
    ACCESS_IPC_CROSS_USERS_LOWER,  // << Allows processes to communicate with lower users (e.g. normal/admin users from services)

    ACCESS_NOTIFICATIONS,          // << Allows the process to send and list notifications
    ACCESS_NOTIFICATION_CONTENTS,  // << Allows the process to read notification contents

    PERFORM_RAW_SYSCALLS,

    LIST_PACKAGES,            // << Allows the process to list packages
    REQUEST_INSTALL_PACKAGES, // << Allows the process to request installation procedures
    REQUEST_REMOVE_PACKAGES,  // << Allows the process to request uninstallation procedures

    ACCESS_LOCK_STATE,        // << Allows to check, whether
    ACCESS_POWER_STATE,       // << Allows access to the current power config and state
    ACCESS_POWER_MANAGEMENT,  // << Allows access to manage power configurations between balance and other configs
    START_UPON_BOOT,          // << Allows programs to launch upon successful boot
    START_UPON_BOOT_COMPLETE, // << Allows programs to launch upon a successful boot, once the user is logged in

    PERFORM_SCREEN_CAPTURE,
    PERFORM_SCREENSHOTS,

    TELEPHONY,              // << Access to Modem Interfaces
    MANAGE_APN_SETTINGS,
    PERFORM_CALLS,
    RECEIVE_CALLS,
    USE_SIP,                // << Manage VoIP / SIP calls
    RWS_SMS_COMMUNICATIONS, // << Receive / Read, Write and Send
    RWS_MMS_COMMUNICATIONS, // << Receive / Read, Write and Send
    READ_PHONE_NUMBERS,     // << Allows the process to access the phone numbers

    MANAGE_DEVICE_STATE,        // << Allows the process to read and write the device state
    MANAGE_CONTACTS,
    MANAGE_CALENDAR,
    MANAGE_CALL_LOGS,
    MANAGE_SETTINGS,
    MANAGE_SECURE_SETTINGS,
    MANAGE_SYSTEM_PREFERENCES,  // << Access to system registry and configurations
    MANAGE_ALARMS,              // << Access to wake-up alarms (e.g. schedule to perform actions, like playing an alarm)

    MANAGE_ACCOUNTS,      // << Read / Insert access to Account Storage
    MANAGE_CREDENTIALS,   // << Read / Write access to Credential Storage
};

struct PELF_PermissionGrantResults {
    enum Level {
        PERMISSION_GRANTED,
        PERMISSION_SPECIFIC_GRANTED,  // granted access to a specific permission (e.g. ACCESS_MEDIA_FILES)
        PERMISSION_DENIED,
        PERMISSION_SPECIFIC_DENIED    // denied access to a specific permission (e.g. ACCESS_MEDIA_FILES)
    };

    PELF_PermissionLabel label;
    Level results;
    bool temporary;              // << Permission will be reset, once the process exits
};

struct PELF_Permission {
    PELF_PermissionLabel name;
    bool required;
    double cLibMaxSdkLevel;
};

struct PELF_Feature {
    std::string name;
    bool required;
    int version;
};

#endif //PELF_LIBPELF_PERMISSIONS_HPP
