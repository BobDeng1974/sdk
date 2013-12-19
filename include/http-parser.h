#ifndef _http_parser_h_
#define _http_parser_h_

#ifdef __cplusplus
extern "C" {
#endif

enum HTTP_PARSER_MODE { 
	HTTP_PARSER_CLIENT = 0, 
	HTTP_PARSER_SERVER = 1
};

/// get/set maximum body size(global setting)
/// @param[in] bytes 0-unlimit, other-limit bytes
int http_get_max_size();
int http_set_max_size(unsigned int bytes);

/// create
/// @param[in] mode 1-server mode, 0-client mode
/// @return parser instance
void* http_parser_create(enum HTTP_PARSER_MODE mode);

/// destroy
/// @return 0-ok, other-error
int http_parser_destroy(void* parser);

/// clear state
void http_parser_clear(void* parser);

/// input data
/// @param[in] data content
/// @param[in/out] bytes out-remain bytes
/// @return 1-need more data, 0-receive done, <0-error
int http_parser_input(void* parser, const void* data, int *bytes);

/// HTTP start-line
int http_get_version(void* parser, int *major, int *minor);
int http_get_status_code(void* parser);
const char* http_get_status_reason(void* parser);
const char* http_get_request_uri(void* parser);
const char* http_get_request_method(void* parser);

/// HTTP body(use with http_get_content_length)
const void* http_get_content(void* parser);

/// HTTP headers
/// @return 0-ok, other-error
int http_get_header_count(void* parser);
/// @return 0-ok, <0-don't have header
int http_get_header(void* parser, int idx, const char** name, const char** value);
/// @return NULL-don't found header, other-header value
const char* http_get_header_by_name(void* parser, const char* name);
/// @return 0-ok, <0-don't have header
int http_get_header_by_name2(void* parser, const char* name, int *value);
/// @return >=0-content-length, <0-don't have content-length header
int http_get_content_length(void* parser);
/// @return 1-close, 0-keep-alive, <0-don't have connection header
int http_get_connection(void* parser);
/// @return Content-Encoding, 0-don't have this header
const char* http_get_content_encoding(void* parser);
/// @return Transfer-Encoding, 0-don't have this header
const char* http_get_transfer_encoding(void* parser);
/// @return Set-Cookie, 0-don't have this header
const char* http_get_cookie(void* parser);
/// @return Location, 0-don't have this header
const char* http_get_location(void* parser);

#ifdef __cplusplus
}
#endif
#endif /* !_http_parser_h_ */
