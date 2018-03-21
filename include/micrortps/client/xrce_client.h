
// Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _MICRORTPS_CLIENT_XRCE_CLIENT_H_
#define _MICRORTPS_CLIENT_XRCE_CLIENT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <microcdr/microcdr.h>

typedef struct BestEffortStream
{
    uint16_t seq_num;

    uint8_t buf[MICRORTPS_MTU_SIZE];
    MicroBuffer micro_buffer;

} BestEffortStream;


typedef struct ReliableStream
{
    uint16_t seq_num;
    uint16_t last_seq_num;

    struct Buffer
    {
        uint8_t buf[MICRORTPS_MTU_SIZE];
        MicroBuffer micro_buffer;

    } store[MICRORTPS_MAX_MSG_NUM];

} ReliableStream;


typedef void (*OnTopic)(uint32_t id, MicroBuffer* message, void *args);

typedef struct Session
{
    SessionId id;
    ClientKey key;
    locator_id_t transport_id;
    uint16_t request_id;

    uint8_t header_offset;

    BestEffortStream input_best_effort_stream;
    BestEffortStream output_best_effort_stream;
    ReliableStream input_reliable_stream;
    ReliableStream output_reliable_stream;

    OnTopic on_topic_callback;
    void* on_topic_args;

    ResultStatus last_status;
    bool last_status_received;

} Session;



uint8_t new_udp_session_sync(Session* session,
                             SessionId id,
                             ClientKey key,
                             uint16_t send_port,
                             uint16_t recv_port,
                             uint16_t remote_port,
                             const char* server_ip,
                             OnTopic on_topic_callback,
                             void* on_topic_args);

void close_session(Session* session);

bool init_session_syn(Session* session);

/**
 * @brief create_participant_by_ref
 *
 * @param session
 * @param object_id
 * @param ref
 * @param reuse
 * @param replace
 *
 * @return
 */
bool create_participant_by_ref(Session* session,
                               const ObjectId object_id,
                               const char* ref,
                               bool reuse,
                               bool replace);
/**
 * @brief create_topic_by_xml
 *
 * @param session
 * @param object_id
 * @param xml
 * @param participant_id
 * @param reuse
 * @param replace
 *
 * @return
 */
bool create_topic_by_xml(Session* session,
                         const ObjectId object_id,
                         const char* xml,
                         const ObjectId participant_id,
                         bool reuse,
                         bool replace);
/**
 * @brief create_publisher_by_xml
 *
 * @param session
 * @param object_id
 * @param xml
 * @param participant_id
 * @param reuse
 * @param replace
 *
 * @return
 */
bool create_publisher_by_xml(Session* session,
                             const ObjectId object_id,
                             const char* xml,
                             const ObjectId participant_id,
                             bool reuse,
                             bool replace);

/**
 * @brief create_subscriber_by_xml
 *
 * @param session
 * @param object_id
 * @param xml
 * @param participant_id
 * @param reuse
 * @param replace
 *
 * @return
 */
bool create_subscriber_by_xml(Session* session,
                              const ObjectId object_id,
                              const char* xml,
                              const ObjectId participant_id,
                              bool reuse,
                              bool replace);
/**
 * @brief create_datawriter_by_xml
 *
 * @param session
 * @param object_id
 * @param xml
 * @param publisher_id
 * @param reuse
 * @param replace
 *
 * @return
 */
bool create_datawriter_by_xml(Session* session,
                              const ObjectId object_id,
                              const char* xml,
                              const ObjectId publisher_id,
                              bool reuse,
                              bool replace);

/**
 * @brief create_datareader_by_xml
 *
 * @param session
 * @param object_id
 * @param xml
 * @param subscriber_id
 * @param reuse
 * @param replace
 *
 * @return
 */
bool create_datareader_by_xml(Session* session,
                                      const ObjectId object_id,
                                      const char* xml,
                                      const ObjectId subscriber_id,
                                      bool reuse,
                                      bool replace);


bool delete_sync(Session* session, ObjectId object_id);

bool read_data_sync(Session* session, ObjectId object_id);

void run_communication(Session* session);

#ifdef __cplusplus
}
#endif

#endif //_MICRORTPS_CLIENT_XRCE_CLIENT_H_