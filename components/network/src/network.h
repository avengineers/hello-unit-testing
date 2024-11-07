#ifndef NETWORK_H
#define NETWORK_H

typedef enum
{
    NETWORK_UNINITIALIZED,
    NETWORK_INITIALIZED,
} NetworkControllerStatus;

typedef enum
{
    FULL_COMMUNICATION,
    NO_COMMUNICATION,
} CommunicationStatus;

/* Network controller status */
extern NetworkControllerStatus getNetworkControllerStatus(void);

/* Communication status */
extern CommunicationStatus getCommunicationStatus(void);

#endif /* NETWORK_H */
