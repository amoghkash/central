#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum messageType_t {
    CONFIG,             // Configuration-related messages (e.g., network settings, parameters).
    ACK,                // Confirmation of receipt of a message.
    DATA,               // General data transmission messages.
    COMMAND,            // Control messages for devices (e.g., turn on/off, reset).
    BEACON,             // Messages used to announce presence or availability.
    ERROR,              // Messages indicating an issue or failure in transmission.
    KEEP_ALIVE,         // Periodic messages to maintain network presence.
    AUTHENTICATION,     // Messages related to verifying device identity.
    SECURITY,           // Messages related to encryption, key exchange, or access control.
    DISCOVERY,          // Messages used to find other devices or services.
    UPDATE,             // Messages related to firmware or configuration updates.
    TIME_SYNC,          // Messages used to synchronize clocks across devices.
    BROADCAST,          // Messages sent to all nodes within range.
    DIAGNOSTIC,         // Messages used for troubleshooting and debugging.
    TELEMETRY,          // Messages carrying sensor or device status data.
    EVENT,              // Notifications of specific occurrences (e.g., motion detected).
    RESERVED            // Placeholder for future message types.
} messageType;

typedef struct meshMessage {
    messageType type;
    char* message;
    int size;
} meshMessage_t;



#ifdef __cplusplus
}
#endif


