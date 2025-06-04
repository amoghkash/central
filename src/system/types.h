#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef enum messageCategory_t {
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
} messageCategory;

typedef enum messageType_t {
    CONFIRMABLE     = 0, ///< Confirmable           - Requires an Acknowledgeable
    NON_CONFIRMABLE = 1, ///< Non-confirmable       - Doesn't require an acknowledge
    ACKNOWLEDGMENT  = 2, ///< Acknowledgment        - Message is an Acknowledgement
    RESET           = 3, ///< Reset                 - Not sure what this is
} messageType;

typedef struct meshMessage_t {
    messageCategory category;
    messageType type;
    uint8_t token;
    char* message;
    int size;
} meshMessage;

typedef struct meshPacket_t {
    uint8_t         device_id[8];
    messageCategory category;
    messageType     type;
    char*           message;
    int             message_size;
} meshPacket;


typedef void (*mesh_handler)(meshMessage* message);

int mesh_send(meshPacket *packet);

typedef struct {
    uint8_t header;          // [2 bits version | 2 bits type | 4 bits token_len]
    uint8_t code;            // maps to messageCategory
    uint16_t message_id;     // Unique ID (random or sequential)
    uint8_t token[15];       // Up to 15-byte token
    uint16_t payload_len;    // Length of message
    uint8_t payload[];       // Flexible array member (actual message)
} BinaryMeshMessage;
#ifdef __cplusplus
}
#endif


