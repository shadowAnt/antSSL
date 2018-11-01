/**
 * [HmacEncode description]
 * @param  algo          [the method of hash function]
 * @param  key           [the key of HMAC]
 * @param  key_length    [the lenth of key]
 * @param  input         [input]
 * @param  input_length  [the lenth of input]
 * @param  output        [output]
 * @param  output_length [description]
 * @return               [1 is success, 0 is error]
 */
int HmacEncode(const char *algo,
               const char *key, unsigned int key_length,
               const char *input, unsigned int input_length,
               unsigned char*&output, unsigned int &output_length);
