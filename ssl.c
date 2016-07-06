#include <stdio.h>
#include <stdlib.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

unsigned char cert_asn1[] = {
  0x30, 0x82, 0x03, 0xc7, 0x30, 0x82, 0x02, 0xaf, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x09, 0x00, 0x96, 0xf5, 0x82, 0x94, 0x4c, 0x76, 0x55, 0x6e,
  0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
  0x0b, 0x05, 0x00, 0x30, 0x7a, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55,
  0x04, 0x06, 0x13, 0x02, 0x46, 0x52, 0x31, 0x0f, 0x30, 0x0d, 0x06, 0x03,
  0x55, 0x04, 0x08, 0x0c, 0x06, 0x46, 0x72, 0x61, 0x6e, 0x63, 0x65, 0x31,
  0x0f, 0x30, 0x0d, 0x06, 0x03, 0x55, 0x04, 0x07, 0x0c, 0x06, 0x53, 0x65,
  0x63, 0x6c, 0x69, 0x6e, 0x31, 0x0d, 0x30, 0x0b, 0x06, 0x03, 0x55, 0x04,
  0x0a, 0x0c, 0x04, 0x42, 0x6c, 0x62, 0x6c, 0x31, 0x0c, 0x30, 0x0a, 0x06,
  0x03, 0x55, 0x04, 0x0b, 0x0c, 0x03, 0x52, 0x26, 0x44, 0x31, 0x0d, 0x30,
  0x0b, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 0x04, 0x41, 0x6c, 0x65, 0x78,
  0x31, 0x1d, 0x30, 0x1b, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
  0x01, 0x09, 0x01, 0x16, 0x0e, 0x62, 0x6c, 0x62, 0x6c, 0x40, 0x67, 0x6d,
  0x61, 0x69, 0x6c, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x1e, 0x17, 0x0d, 0x31,
  0x36, 0x30, 0x36, 0x33, 0x30, 0x30, 0x38, 0x33, 0x37, 0x32, 0x37, 0x5a,
  0x17, 0x0d, 0x31, 0x37, 0x30, 0x36, 0x33, 0x30, 0x30, 0x38, 0x33, 0x37,
  0x32, 0x37, 0x5a, 0x30, 0x7a, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55,
  0x04, 0x06, 0x13, 0x02, 0x46, 0x52, 0x31, 0x0f, 0x30, 0x0d, 0x06, 0x03,
  0x55, 0x04, 0x08, 0x0c, 0x06, 0x46, 0x72, 0x61, 0x6e, 0x63, 0x65, 0x31,
  0x0f, 0x30, 0x0d, 0x06, 0x03, 0x55, 0x04, 0x07, 0x0c, 0x06, 0x53, 0x65,
  0x63, 0x6c, 0x69, 0x6e, 0x31, 0x0d, 0x30, 0x0b, 0x06, 0x03, 0x55, 0x04,
  0x0a, 0x0c, 0x04, 0x42, 0x6c, 0x62, 0x6c, 0x31, 0x0c, 0x30, 0x0a, 0x06,
  0x03, 0x55, 0x04, 0x0b, 0x0c, 0x03, 0x52, 0x26, 0x44, 0x31, 0x0d, 0x30,
  0x0b, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 0x04, 0x41, 0x6c, 0x65, 0x78,
  0x31, 0x1d, 0x30, 0x1b, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d,
  0x01, 0x09, 0x01, 0x16, 0x0e, 0x62, 0x6c, 0x62, 0x6c, 0x40, 0x67, 0x6d,
  0x61, 0x69, 0x6c, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x82, 0x01, 0x22, 0x30,
  0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01,
  0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02,
  0x82, 0x01, 0x01, 0x00, 0xd7, 0xc1, 0x1b, 0x13, 0xf0, 0xfe, 0xa4, 0x92,
  0xdd, 0x54, 0x67, 0xd3, 0x58, 0xca, 0xa2, 0x93, 0xb2, 0x05, 0x06, 0xdb,
  0x13, 0xec, 0x4a, 0xfc, 0x37, 0xe2, 0xb8, 0x94, 0xe8, 0x76, 0xdb, 0x0c,
  0x8d, 0x67, 0x1f, 0x05, 0xbd, 0x31, 0x53, 0x50, 0xd5, 0x10, 0x41, 0xa5,
  0xbb, 0xb3, 0x79, 0xf6, 0xc9, 0xcf, 0x0d, 0xe2, 0xcd, 0x9c, 0x1c, 0xbe,
  0x70, 0xf5, 0x23, 0x23, 0xca, 0x0a, 0x89, 0xe6, 0x32, 0xf8, 0x02, 0x7f,
  0x06, 0xef, 0x9a, 0x08, 0x48, 0xf1, 0xe6, 0x86, 0xc8, 0x5e, 0xd3, 0x11,
  0xb3, 0x98, 0x8c, 0xc3, 0x20, 0xbc, 0x3b, 0xe6, 0x53, 0x11, 0x2a, 0xec,
  0x3d, 0x0e, 0x96, 0xd7, 0xc9, 0xea, 0xf2, 0x09, 0x04, 0xfe, 0xd3, 0xc2,
  0x29, 0x86, 0x51, 0x67, 0xed, 0x69, 0x3a, 0x82, 0x5a, 0xca, 0x45, 0xb6,
  0x5f, 0x1b, 0x63, 0x31, 0x63, 0x32, 0x2b, 0xf3, 0xd9, 0xbd, 0x51, 0xc0,
  0x6f, 0xd0, 0x8a, 0x30, 0x57, 0x27, 0xa1, 0x03, 0x60, 0x37, 0x86, 0x9a,
  0xfa, 0x3b, 0x74, 0x26, 0xb6, 0xf9, 0xa9, 0x2e, 0xde, 0x36, 0xc2, 0x6c,
  0x84, 0xb3, 0x43, 0xde, 0x28, 0xb0, 0xe4, 0x13, 0xff, 0x42, 0xb8, 0x59,
  0x9b, 0x13, 0x87, 0xf5, 0xc9, 0xe0, 0xdd, 0x30, 0xd5, 0x12, 0xe9, 0x2e,
  0x35, 0xb2, 0x37, 0x50, 0x76, 0x8a, 0x76, 0xc9, 0x71, 0xcd, 0xce, 0xf7,
  0xef, 0x23, 0x33, 0x07, 0x2a, 0x0b, 0x8e, 0x9e, 0xee, 0xb7, 0xb2, 0xf0,
  0x59, 0xd1, 0x2f, 0xb6, 0x2f, 0x1c, 0x98, 0x0f, 0x78, 0x4b, 0x71, 0xed,
  0x9e, 0xf2, 0xb7, 0x3f, 0xee, 0x5b, 0x01, 0x00, 0x9e, 0xf4, 0x61, 0x1b,
  0x95, 0xc6, 0xd3, 0x37, 0xa7, 0xb1, 0x99, 0x51, 0xcc, 0x04, 0x88, 0xf1,
  0x51, 0xf3, 0x14, 0xa5, 0x8c, 0xd6, 0xe7, 0x58, 0x35, 0x13, 0x54, 0xe2,
  0xe4, 0xc2, 0x2b, 0xee, 0x2c, 0x56, 0x13, 0xf9, 0x02, 0x03, 0x01, 0x00,
  0x01, 0xa3, 0x50, 0x30, 0x4e, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e,
  0x04, 0x16, 0x04, 0x14, 0x84, 0x3f, 0x19, 0xf2, 0xa6, 0x9c, 0x50, 0x23,
  0x16, 0x0b, 0x0f, 0xe4, 0xdc, 0x7a, 0x51, 0xed, 0x72, 0x2e, 0x01, 0x08,
  0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80,
  0x14, 0x84, 0x3f, 0x19, 0xf2, 0xa6, 0x9c, 0x50, 0x23, 0x16, 0x0b, 0x0f,
  0xe4, 0xdc, 0x7a, 0x51, 0xed, 0x72, 0x2e, 0x01, 0x08, 0x30, 0x0c, 0x06,
  0x03, 0x55, 0x1d, 0x13, 0x04, 0x05, 0x30, 0x03, 0x01, 0x01, 0xff, 0x30,
  0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b,
  0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0xaf, 0xba, 0x1f, 0xff, 0xfa,
  0xa4, 0x6e, 0x1a, 0x8c, 0x72, 0xb7, 0xeb, 0x3e, 0xda, 0xc9, 0x06, 0x78,
  0x6b, 0x5b, 0x75, 0x12, 0xd2, 0x63, 0xfa, 0x38, 0xd2, 0x9b, 0xb8, 0x5c,
  0x9e, 0xde, 0x31, 0xdf, 0xd9, 0xb1, 0x6e, 0xf7, 0x7d, 0x65, 0xf9, 0xa7,
  0x2e, 0x7b, 0x37, 0x87, 0x81, 0xef, 0x60, 0x67, 0x21, 0xb8, 0xff, 0x3b,
  0xee, 0x60, 0x97, 0x5a, 0x57, 0x7d, 0xcb, 0x00, 0xff, 0x3f, 0x85, 0x8e,
  0xde, 0xa1, 0x02, 0xdf, 0x08, 0x92, 0xd1, 0x85, 0x23, 0xb3, 0x29, 0xf2,
  0x40, 0x91, 0xca, 0x3f, 0x4a, 0x12, 0xc8, 0x13, 0xe0, 0xe7, 0x71, 0x66,
  0xd0, 0xe1, 0x52, 0x7f, 0xbc, 0xfd, 0x28, 0x77, 0x6a, 0xcd, 0xa1, 0x93,
  0x2a, 0x12, 0x2e, 0x6e, 0xd6, 0x16, 0x0b, 0x8e, 0x01, 0xf8, 0xb3, 0xd3,
  0x9c, 0x94, 0x0c, 0xb4, 0x9d, 0x85, 0xa9, 0x45, 0x5e, 0xd4, 0x23, 0x34,
  0xbf, 0x02, 0x2e, 0x24, 0x6d, 0x27, 0x6c, 0x67, 0x56, 0x38, 0x1a, 0x62,
  0x29, 0x2d, 0xc5, 0xba, 0x65, 0x4e, 0x04, 0x97, 0x95, 0xa4, 0x16, 0x45,
  0x59, 0x4a, 0x78, 0x4b, 0x7d, 0x54, 0x2a, 0xe7, 0xcb, 0x79, 0x07, 0xfa,
  0xcc, 0xcc, 0xb3, 0xe6, 0xf0, 0x0c, 0x72, 0xf6, 0x84, 0x56, 0xb7, 0xac,
  0x1b, 0x64, 0xcb, 0x35, 0xd5, 0xc7, 0x98, 0x73, 0x62, 0xef, 0x06, 0x25,
  0xaf, 0x96, 0x83, 0x91, 0xad, 0xe7, 0xa9, 0x04, 0x63, 0xdf, 0x8e, 0xcd,
  0xc0, 0xeb, 0x46, 0x16, 0xc7, 0x41, 0x63, 0x9d, 0x13, 0xd6, 0x67, 0xe8,
  0x29, 0x9b, 0xab, 0xb5, 0xa0, 0xad, 0x63, 0x18, 0xa6, 0xaa, 0x46, 0x75,
  0xce, 0xe3, 0xfc, 0x5f, 0x4c, 0xca, 0xc7, 0x79, 0x73, 0xc3, 0x65, 0x22,
  0xf6, 0xc4, 0xd3, 0x67, 0x21, 0x66, 0x3a, 0xd0, 0x47, 0xbb, 0xb2, 0x36,
  0x4d, 0x07, 0xbe, 0x2c, 0xb1, 0x35, 0xdf, 0xdf, 0xb2, 0x52, 0x4f
};

unsigned int cert_asn1_len = 971;

unsigned char key_asn1_rsa[] = {
  0x30, 0x82, 0x04, 0xa5, 0x02, 0x01, 0x00, 0x02, 0x82, 0x01, 0x01, 0x00,
  0xd7, 0xc1, 0x1b, 0x13, 0xf0, 0xfe, 0xa4, 0x92, 0xdd, 0x54, 0x67, 0xd3,
  0x58, 0xca, 0xa2, 0x93, 0xb2, 0x05, 0x06, 0xdb, 0x13, 0xec, 0x4a, 0xfc,
  0x37, 0xe2, 0xb8, 0x94, 0xe8, 0x76, 0xdb, 0x0c, 0x8d, 0x67, 0x1f, 0x05,
  0xbd, 0x31, 0x53, 0x50, 0xd5, 0x10, 0x41, 0xa5, 0xbb, 0xb3, 0x79, 0xf6,
  0xc9, 0xcf, 0x0d, 0xe2, 0xcd, 0x9c, 0x1c, 0xbe, 0x70, 0xf5, 0x23, 0x23,
  0xca, 0x0a, 0x89, 0xe6, 0x32, 0xf8, 0x02, 0x7f, 0x06, 0xef, 0x9a, 0x08,
  0x48, 0xf1, 0xe6, 0x86, 0xc8, 0x5e, 0xd3, 0x11, 0xb3, 0x98, 0x8c, 0xc3,
  0x20, 0xbc, 0x3b, 0xe6, 0x53, 0x11, 0x2a, 0xec, 0x3d, 0x0e, 0x96, 0xd7,
  0xc9, 0xea, 0xf2, 0x09, 0x04, 0xfe, 0xd3, 0xc2, 0x29, 0x86, 0x51, 0x67,
  0xed, 0x69, 0x3a, 0x82, 0x5a, 0xca, 0x45, 0xb6, 0x5f, 0x1b, 0x63, 0x31,
  0x63, 0x32, 0x2b, 0xf3, 0xd9, 0xbd, 0x51, 0xc0, 0x6f, 0xd0, 0x8a, 0x30,
  0x57, 0x27, 0xa1, 0x03, 0x60, 0x37, 0x86, 0x9a, 0xfa, 0x3b, 0x74, 0x26,
  0xb6, 0xf9, 0xa9, 0x2e, 0xde, 0x36, 0xc2, 0x6c, 0x84, 0xb3, 0x43, 0xde,
  0x28, 0xb0, 0xe4, 0x13, 0xff, 0x42, 0xb8, 0x59, 0x9b, 0x13, 0x87, 0xf5,
  0xc9, 0xe0, 0xdd, 0x30, 0xd5, 0x12, 0xe9, 0x2e, 0x35, 0xb2, 0x37, 0x50,
  0x76, 0x8a, 0x76, 0xc9, 0x71, 0xcd, 0xce, 0xf7, 0xef, 0x23, 0x33, 0x07,
  0x2a, 0x0b, 0x8e, 0x9e, 0xee, 0xb7, 0xb2, 0xf0, 0x59, 0xd1, 0x2f, 0xb6,
  0x2f, 0x1c, 0x98, 0x0f, 0x78, 0x4b, 0x71, 0xed, 0x9e, 0xf2, 0xb7, 0x3f,
  0xee, 0x5b, 0x01, 0x00, 0x9e, 0xf4, 0x61, 0x1b, 0x95, 0xc6, 0xd3, 0x37,
  0xa7, 0xb1, 0x99, 0x51, 0xcc, 0x04, 0x88, 0xf1, 0x51, 0xf3, 0x14, 0xa5,
  0x8c, 0xd6, 0xe7, 0x58, 0x35, 0x13, 0x54, 0xe2, 0xe4, 0xc2, 0x2b, 0xee,
  0x2c, 0x56, 0x13, 0xf9, 0x02, 0x03, 0x01, 0x00, 0x01, 0x02, 0x82, 0x01,
  0x01, 0x00, 0xa9, 0xa0, 0x1b, 0xae, 0xd8, 0xe9, 0x0a, 0xf0, 0xa0, 0x6c,
  0x4c, 0xd8, 0x9f, 0xd5, 0x68, 0x6e, 0x60, 0x26, 0x8d, 0x96, 0x4e, 0x1a,
  0x97, 0x75, 0xa6, 0x66, 0x6c, 0xa2, 0x3e, 0x05, 0xbc, 0x00, 0x29, 0x67,
  0xea, 0xbe, 0xf3, 0x58, 0xc5, 0x5d, 0x26, 0xb6, 0x0a, 0x36, 0xc7, 0xd4,
  0xba, 0x4d, 0xe9, 0xaa, 0x0d, 0x0b, 0xc4, 0x85, 0x39, 0x20, 0x0c, 0xe4,
  0xdd, 0xc4, 0xb4, 0x83, 0x06, 0x99, 0xe2, 0x76, 0x94, 0x57, 0xd4, 0x57,
  0x2a, 0x2d, 0xdb, 0x53, 0xbb, 0xdf, 0x39, 0xc7, 0x3b, 0x80, 0x8e, 0x47,
  0xa0, 0x5b, 0x84, 0xf0, 0x18, 0xd3, 0xe3, 0x78, 0xfa, 0xdb, 0x12, 0xc1,
  0xd6, 0x9c, 0x3f, 0x16, 0xa5, 0x45, 0xac, 0x14, 0xc0, 0xdd, 0xc5, 0x11,
  0xe2, 0x0c, 0xa8, 0x5d, 0xf3, 0xef, 0x2a, 0x7c, 0x1e, 0xc4, 0xdc, 0x0f,
  0x47, 0x34, 0x3b, 0xfd, 0xe5, 0x0a, 0x69, 0xa4, 0xeb, 0x90, 0xc2, 0xc9,
  0xc9, 0xe4, 0x79, 0x9b, 0x53, 0x76, 0xb3, 0xa9, 0xa6, 0x22, 0xb4, 0x63,
  0x5a, 0xf2, 0x91, 0x59, 0x6a, 0xd0, 0xbb, 0x63, 0x69, 0xac, 0xe5, 0x14,
  0x1f, 0xc7, 0x69, 0xaf, 0x09, 0x63, 0x9f, 0x52, 0x5d, 0xc7, 0x7a, 0x62,
  0x98, 0x3e, 0x30, 0x37, 0xf9, 0x39, 0x86, 0x52, 0x4d, 0x11, 0x05, 0x12,
  0xd1, 0xf6, 0x56, 0xa8, 0x08, 0x2c, 0xac, 0xfb, 0xd0, 0x18, 0x21, 0x67,
  0x35, 0x42, 0xcf, 0xcc, 0x53, 0x91, 0xaa, 0x52, 0x59, 0xdb, 0x35, 0x4b,
  0xf9, 0x5c, 0x74, 0x23, 0x74, 0x88, 0xb9, 0xed, 0x1b, 0xc9, 0x33, 0x0d,
  0x2c, 0x9a, 0x38, 0x9f, 0xec, 0x23, 0x95, 0x88, 0x15, 0x7c, 0xd8, 0xff,
  0x72, 0xb4, 0x09, 0xd6, 0xfc, 0x76, 0x71, 0x0a, 0xf5, 0x2c, 0xd8, 0x0f,
  0x99, 0xd1, 0x13, 0x04, 0xed, 0x4a, 0xbb, 0x43, 0x52, 0xea, 0x82, 0xad,
  0x5d, 0xc3, 0x4e, 0xe8, 0xe7, 0xc5, 0x02, 0x81, 0x81, 0x00, 0xfa, 0x96,
  0x37, 0xe5, 0xb9, 0x52, 0x86, 0x46, 0xf0, 0x10, 0x05, 0xb1, 0xa8, 0x47,
  0xae, 0x31, 0xff, 0x13, 0x9b, 0x84, 0xd0, 0x65, 0x78, 0x9e, 0x2f, 0xff,
  0xa5, 0x74, 0xa5, 0xef, 0x52, 0xab, 0xc1, 0xb3, 0x57, 0xde, 0xb6, 0x96,
  0xea, 0xf1, 0x8c, 0x15, 0x88, 0xc6, 0x78, 0xa8, 0xd3, 0xa3, 0x10, 0x01,
  0x84, 0x26, 0xb2, 0x24, 0xab, 0xa9, 0x4d, 0x05, 0x22, 0xd6, 0xb0, 0xba,
  0xfc, 0x6c, 0x2a, 0x6a, 0x90, 0x30, 0xd8, 0xef, 0xb9, 0x84, 0xca, 0x4a,
  0x51, 0xb5, 0xe9, 0xe6, 0x6c, 0xad, 0x4b, 0x1d, 0xf4, 0x14, 0xa7, 0x39,
  0x38, 0x6e, 0xf2, 0x01, 0x4d, 0x02, 0xf0, 0x7b, 0x5d, 0x54, 0x16, 0x0a,
  0x05, 0x19, 0x20, 0x8d, 0xe0, 0xc6, 0xf8, 0x4f, 0xf4, 0x14, 0x1b, 0xf8,
  0xf7, 0xa9, 0xf9, 0x93, 0x4f, 0x5f, 0xa4, 0x3b, 0xfc, 0x78, 0xa9, 0x49,
  0x0c, 0xc0, 0x6d, 0xfe, 0x44, 0x1f, 0x02, 0x81, 0x81, 0x00, 0xdc, 0x6a,
  0x42, 0x3d, 0xf5, 0x99, 0xef, 0x46, 0xdd, 0x21, 0x7c, 0xdd, 0x85, 0xbb,
  0xb6, 0x62, 0x99, 0x71, 0x2a, 0x1e, 0x2f, 0x90, 0x06, 0xf9, 0x42, 0x75,
  0x14, 0xdb, 0x8c, 0xb0, 0xd9, 0x48, 0x5b, 0xfa, 0x1f, 0xaf, 0xe6, 0x75,
  0x79, 0xbb, 0x4c, 0x0e, 0xd2, 0xf8, 0x3b, 0x92, 0xdf, 0x90, 0x88, 0x47,
  0xbc, 0x67, 0x59, 0x22, 0xfa, 0x79, 0xf9, 0x02, 0x61, 0x74, 0x43, 0xa9,
  0x7b, 0x0e, 0x4d, 0x25, 0x69, 0x57, 0x67, 0x93, 0xac, 0xe5, 0xe9, 0xc9,
  0xb8, 0x34, 0x2e, 0xee, 0xf7, 0xd3, 0x2a, 0xbd, 0x2f, 0x97, 0xbc, 0xcf,
  0xca, 0x63, 0xc0, 0xc3, 0x4f, 0x15, 0x7c, 0xb0, 0xbc, 0x68, 0x5d, 0x8c,
  0x4d, 0xf4, 0x92, 0x4d, 0xb5, 0x34, 0xd2, 0x04, 0xe4, 0x00, 0xb4, 0x51,
  0x5c, 0x29, 0xcd, 0x79, 0x7a, 0xe3, 0x24, 0xdc, 0x80, 0x72, 0x5a, 0x51,
  0x65, 0x91, 0x89, 0x65, 0xe4, 0xe7, 0x02, 0x81, 0x80, 0x67, 0x20, 0x49,
  0x32, 0xce, 0x78, 0xea, 0xef, 0xe8, 0xbd, 0xff, 0x49, 0xe4, 0xe2, 0x53,
  0x0b, 0x1a, 0x59, 0x9c, 0x68, 0x25, 0x47, 0x8d, 0x43, 0x34, 0xa7, 0xb6,
  0x14, 0xf2, 0x71, 0x32, 0x89, 0xa2, 0xf6, 0xc6, 0xd3, 0xce, 0x3a, 0xff,
  0xc7, 0x96, 0x8a, 0x0a, 0x36, 0xfb, 0xd3, 0x26, 0xfd, 0xf5, 0x89, 0x5a,
  0x34, 0x7e, 0x9d, 0xde, 0xd3, 0x96, 0xf1, 0xe5, 0x2b, 0x8b, 0xa1, 0xf8,
  0x5e, 0x1f, 0x7a, 0xa9, 0x8a, 0xa0, 0xcc, 0xcf, 0x81, 0x99, 0xaa, 0xca,
  0x43, 0xde, 0x55, 0xc9, 0x25, 0xec, 0x43, 0x10, 0x7f, 0x2b, 0x6e, 0xbe,
  0x0d, 0xd2, 0xa4, 0xbc, 0x67, 0xd8, 0x46, 0x3c, 0xdb, 0x6d, 0x12, 0x84,
  0x94, 0x99, 0xb4, 0x29, 0xec, 0x58, 0xa6, 0xb6, 0xe1, 0x4b, 0xbd, 0xc3,
  0x56, 0xfd, 0x72, 0x25, 0x79, 0x4b, 0xe2, 0xaf, 0xfd, 0x8c, 0x55, 0x96,
  0xdc, 0xde, 0xa7, 0x84, 0xab, 0x02, 0x81, 0x81, 0x00, 0x81, 0xc5, 0x09,
  0xd5, 0x22, 0xd9, 0x8b, 0x97, 0xe4, 0x2f, 0x88, 0x2d, 0x80, 0x44, 0x21,
  0x40, 0x71, 0xe8, 0xbf, 0x8c, 0x60, 0x22, 0x63, 0x08, 0xb4, 0x08, 0xec,
  0xcb, 0xca, 0x4c, 0x80, 0xd0, 0xea, 0x5e, 0x1b, 0xf3, 0xdb, 0x32, 0x85,
  0x06, 0x31, 0xe4, 0x74, 0x6f, 0x73, 0xdb, 0xa8, 0x46, 0x97, 0x05, 0xed,
  0x35, 0xc7, 0xb4, 0x21, 0x56, 0x58, 0xb5, 0xff, 0x1c, 0x8d, 0x8d, 0xa6,
  0x06, 0xa8, 0x83, 0x03, 0x3f, 0x53, 0x9b, 0x0d, 0x6b, 0x9b, 0xb6, 0x88,
  0xfe, 0x28, 0x37, 0xc7, 0xaf, 0x0a, 0xf5, 0xb1, 0xa4, 0x9b, 0xa4, 0x97,
  0x1b, 0x1d, 0xed, 0x9f, 0x8d, 0x1e, 0x09, 0x8c, 0x13, 0xc2, 0x28, 0x0d,
  0xe9, 0x95, 0x8d, 0xac, 0xc7, 0x39, 0x73, 0x69, 0xad, 0xc4, 0x7c, 0x36,
  0x4f, 0xe2, 0x4a, 0xc8, 0x80, 0x1d, 0x3e, 0xb9, 0x5d, 0x1a, 0x31, 0xdc,
  0x23, 0xd0, 0x8a, 0x2e, 0x37, 0x02, 0x81, 0x81, 0x00, 0x99, 0xfb, 0x98,
  0x3f, 0xd9, 0xc2, 0xf6, 0x6c, 0xb0, 0xc7, 0x5f, 0x48, 0x38, 0xe4, 0x57,
  0x01, 0xa3, 0x46, 0x6c, 0xbe, 0x04, 0xf5, 0xb8, 0x20, 0x28, 0x50, 0xac,
  0x34, 0x4c, 0x48, 0xca, 0x04, 0x51, 0x0d, 0x7e, 0xcf, 0x94, 0xf9, 0x51,
  0xf9, 0xe5, 0x2b, 0xe6, 0x2b, 0x07, 0x4e, 0x86, 0x6f, 0x63, 0xea, 0xf9,
  0x3a, 0x0c, 0x19, 0xbf, 0xc6, 0xf7, 0xdb, 0xc4, 0x53, 0x67, 0x27, 0x3a,
  0xc9, 0x7a, 0x0f, 0xfe, 0xc1, 0xec, 0x1c, 0x0a, 0x57, 0x3a, 0x8c, 0x13,
  0x70, 0xa5, 0x11, 0x7a, 0x5e, 0x04, 0xed, 0x53, 0xd0, 0x13, 0x04, 0x26,
  0x4e, 0xb8, 0xdd, 0xa7, 0xcf, 0xc2, 0x67, 0x52, 0xaf, 0x20, 0x3d, 0x07,
  0xb4, 0x6a, 0xd8, 0x23, 0x92, 0xc8, 0x06, 0x3e, 0xed, 0x25, 0x61, 0x56,
  0xa3, 0x50, 0xd6, 0xe7, 0x44, 0x74, 0xb3, 0x57, 0xc7, 0x2b, 0x9a, 0xac,
  0xa9, 0xe6, 0x5c, 0xf5, 0x67
};

unsigned int key_asn1_rsa_len = 1193;

SSL* create_ssl_context(SSL_CTX* ctx)
{
	SSL* ssl;

	if (SSL_CTX_use_certificate_ASN1(ctx, cert_asn1_len, cert_asn1) <= 0)
	{
		fprintf(stderr, "Failed to load certificate.\n");
		return NULL;
	}

	/*
	if (SSL_CTX_use_certificate_file(ctx, "/path/to/my/cert.pem", SSL_FILETYPE_PEM) <= 0)
	{
		fprintf(stderr, "Failed to load certificate.\n");
		return NULL;
	}
	*/
	
	if (SSL_CTX_use_RSAPrivateKey_ASN1(ctx, key_asn1_rsa, (long)key_asn1_rsa_len) <= 0)
	{
		ERR_print_errors_fp(stdout);
		fprintf(stderr, "Failed to load key.\n");
		return NULL;
	}

	/*
	if (SSL_CTX_use_PrivateKey_file(ctx, "/path/to/my/key.pem", SSL_FILETYPE_PEM) <= 0)
	{
		fprintf(stderr, "Failed to load certificate.\n");
		return NULL;
	}
	*/

	if (SSL_CTX_load_verify_locations(ctx, "/path/to/my/cert.pem", "/path/to/my/") <= 0)
	{
		fprintf(stderr, "Failed to verify location.\n");
		return NULL;
	}

	if (!SSL_CTX_check_private_key(ctx))
	{
		fprintf(stderr, "Private key does not match the public certificate.\n");
		return NULL;
	}

	SSL_CTX_set_verify(ctx, (SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT), NULL);

	//Creating SSL context

	ssl = SSL_new(ctx);

	return ssl;
}
