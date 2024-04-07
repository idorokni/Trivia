#include "Requests.h"
#include "Buffer.h"

#define LOGIN_REQUEST_CODE 51
#define SIGNUP_REQUEST_CODE 52

class JsonRequestPacketDeserializer {
public:
	LoginRequest deserializeLoginRequest(Buffer buff);
	SignUpRequest deserializeSignupRequest(Buffer buff);
};