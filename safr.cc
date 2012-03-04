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

#include "safr.h"

void SafrInstance::HandleMessage(const pp::Var& var_message) {
    // TODO(sdk_user): 1. Make this function handle the incoming message.
    if (var_message == "register") {
        if (register_algs()) {
            PostMessage("OK");
        } else {
            PostMessage("FAIL");
        }
    } else if (var_message == "test") {
        if (test()) {
            PostMessage("OK");
        } else {
            PostMessage("FAIL");
        }
    } else {
        Json::Value data;
        Json::Reader reader;
        bool parsed = reader.parse(var_message.AsString().c_str(), data);
        if (!parsed) {
            return;
        }

        std::string action = data.get("action", "").asString();
        if (action == "md5") {
            std::string str = data.get("text", "").asString();
            if (str.empty()) return;

            const char* tmp = str.c_str();
            md5sum(tmp);
        } else if (action == "sha1") {
            std::string str = data.get("text", "").asString();
            if (str.empty()) return;

            const char* tmp = str.c_str();
            sha1sum(tmp);
        }
    }
}

bool SafrInstance::register_algs() {
    if (register_cipher(&aes_desc) == -1) return false;
    if (register_hash(&sha1_desc) == -1) return false;
    if (register_hash(&sha256_desc) == -1) return false;
    if (register_hash(&md5_desc) == -1) return false;

    aes_idx = find_cipher("aes");
    sha1_idx = find_hash("sha1");
    sha256_idx = find_hash("sha256");
    md5_idx = find_hash("md5");

    return true;
}

bool SafrInstance::test() {
    if (aes_idx == -1) return false;
    if (sha1_idx == -1) return false;
    if (sha256_idx == -1) return false;
    if (md5_idx == -1) return false;
    return true;
}

void SafrInstance::crypt (const char* salt, const char* text) {
    if ((aes_idx == -1) || (sha256_idx == -1)) return;

    ivsize = cipher_descriptor[aes_idx].block_length;
    ks = hash_descriptor[sha256_idx].hashsize;
    if (cipher_descriptor[aes_idx].keysize(&ks) != CRYPT_OK) {
        return;
    }
}

void SafrInstance::decrypt (const char* salt, const char* str) {
}

void SafrInstance::sha1sum (const char* text) {
    if (sha1_idx == -1) return;

    unsigned char tmp[20];
    hash_descriptor[sha1_idx].init(&md);
    hash_descriptor[sha1_idx].process(&md, (unsigned char *)text,strlen(text));
    hash_descriptor[sha1_idx].done(&md, tmp);

    char buffer[32] = "";
    char str[4];
    for (i = 0; i < (int)hash_descriptor[sha1_idx].hashsize; i++) {
        sprintf(str, "%02x",tmp[i]);
        strcat(buffer, str);
    }
    PostMessage(buffer);
}

void SafrInstance::md5sum (const char* text) {
    if (md5_idx == -1) return;

    unsigned char tmp[16];
    hash_descriptor[md5_idx].init(&md);
    hash_descriptor[md5_idx].process(&md, (unsigned char *)text,strlen(text));
    hash_descriptor[md5_idx].done(&md, tmp);

    char buffer[32] = "";
    char str[4];
    for (i = 0; i < (int)hash_descriptor[md5_idx].hashsize; i++) {
        sprintf(str, "%02x",tmp[i]);
        strcat(buffer, str);
    }
    PostMessage(buffer);
}

class SafrModule : public pp::Module {
 public:
    SafrModule() : pp::Module() {}
    virtual ~SafrModule() {}

    virtual pp::Instance* CreateInstance(PP_Instance instance) {
        return new SafrInstance(instance);
    }
};

namespace pp {
Module* CreateModule() {
    return new SafrModule();
}
}
