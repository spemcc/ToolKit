
/* Author: smccrear */

#ifndef _PROTOHELP_
#define _PROTOHELP_

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <iostream>
#include <arpa/inet.h>
#include <vector>

namespace proto_help {
  
const int kHeaderSize = 8; /* Size - 4Bytes Type - 4Bytes */ 

void PackHeader(const ::google::protobuf::Message& msg, std::vector<uint8_t>* output)
{
  uint32_t size = 0;
  uint32_t msg_type = 0;

  const ::google::protobuf::Reflection * ref = msg.GetReflection();

  /* See if we have MessageType Enum in our .proto */
  const ::google::protobuf::Descriptor* descriptor = msg.GetDescriptor();
  assert(descriptor);
  const ::google::protobuf::EnumDescriptor* edesc = descriptor->FindEnumTypeByName("MessageType");
  assert(edesc);

  /* Get value of MessageType Enum */
  const ::google::protobuf::FieldDescriptor * fdesc = descriptor->field(edesc->index());
  assert(fdesc);
  const ::google::protobuf::EnumValueDescriptor* eval = ref->GetEnum(msg,fdesc);
  assert(eval);

  std::string pb_output; 
  msg.SerializeToString(&pb_output);

  /* set size and msg_type */
  msg_type = eval->number();
  size = pb_output.length();
  output->resize(kHeaderSize + size);

  uint32_t htonl_size = htonl(size);
  uint32_t htonl_msg_type = htonl(msg_type);

  std::vector<uint8_t>& output_ref = *output;
  output_ref[0] = ((htonl_size >> 0)  & 0xFF);
  output_ref[1] = ((htonl_size >> 8)  & 0xFF);
  output_ref[2] = ((htonl_size >> 16) & 0xFF);
  output_ref[3] = ((htonl_size >> 24) & 0xFF);

  output_ref[4] = ((htonl_msg_type >> 0)  & 0xFF);
  output_ref[5] = ((htonl_msg_type >> 8)  & 0xFF);
  output_ref[6] = ((htonl_msg_type >> 16) & 0xFF);
  output_ref[7] = ((htonl_msg_type >> 24) & 0xFF);

  for(uint32_t i = 0; i < size; i++)
    output_ref[kHeaderSize+i] = pb_output[i];

}

void UnpackHeader(const std::vector<uint8_t>& input, uint32_t* size, uint32_t* msg_type)
{
  /*
  for(int i=0,j=0; i < kHeaderSize/2; i++, j+=8)
  {
    *size = (input[i]);
    *size <<= j;
    *msg_type = (input[i+(kHeaderSize/2)]);
    *msg_type <<= j;
  }
  */

  /*
  *size = (input[0]);
  *size <<= 0;
  *size = (input[1]);
  *size <<= 8;
  *size = (input[2]);
  *size <<= 16;
  *size = (input[3]);
  *size <<= 24;
  
  *msg_type = (input[0]);
  *msg_type <<= 0;
  *msg_type = (input[1]);
  *msg_type <<= 8;
  *msg_type = (input[2]);
  *msg_type <<= 16;
  *msg_type = (input[3]);
  *msg_type <<= 24;

  *size = ntohl(*size);
  *msg_type = ntohl(*msg_type);
  */

  *size = ntohl(*((uint32_t*) (&(input.at(0))) ));
  *msg_type = ntohl(*((uint32_t*) (&(input.at(4))) ));
}

};


#endif  /* _PROTOHELP_ */
