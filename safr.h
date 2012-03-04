// Copyright (c) 2012 FTSY
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef SAFR_H_
#define SAFR_H_

#include <cstdio>
#include <string>
#include <tomcrypt.h>
#include <json/json.h>
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

class SafrInstance : public pp::Instance {
  public:
    explicit SafrInstance(PP_Instance instance) : pp::Instance(instance) {};
    virtual ~SafrInstance() {};
    void HandleMessage(const pp::Var& var_message);

  private:
    unsigned char plaintext[512],ciphertext[512];
    unsigned char tmpkey[512], key[MAXBLOCKSIZE], IV[MAXBLOCKSIZE];
    unsigned char inbuf[512]; /* i/o block size */
    unsigned long outlen, ivsize, x, y, z;
    symmetric_CTR ctr;
    int sha1_idx, sha256_idx, md5_idx, aes_idx, ks, i, j, k;
    unsigned long w;
    hash_state md;

    bool register_algs();
    bool test();
    void crypt (const char* salt, const char* text);
    void decrypt (const char* salt, const char* str);
    void sha1sum (const char* text);
    void md5sum (const char* text);
};

#endif // SAFR_H_