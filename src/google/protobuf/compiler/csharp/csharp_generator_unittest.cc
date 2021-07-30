// Protocol Buffers - Google's data interchange format
// Copyright 2014 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <memory>

#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/compiler/csharp/csharp_options.h>
#include <google/protobuf/compiler/csharp/csharp_helpers.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/printer.h>

#include <google/protobuf/testing/googletest.h>
#include <gtest/gtest.h>
#include <google/protobuf/testing/file.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {
namespace {

TEST(CSharpEnumValue, PascalCasedPrefixStripping) {
  struct Options options;
  options.preserve_enums.insert("Bar");
  EXPECT_EQ("Bar", GetEnumValueName("Foo", "BAR", &options));
  EXPECT_EQ("BarBaz", GetEnumValueName("Foo", "BAR_BAZ", &options));
  EXPECT_EQ("Bar", GetEnumValueName("Foo", "FOO_BAR", &options));
  EXPECT_EQ("Bar", GetEnumValueName("Foo", "FOO__BAR", &options));
  EXPECT_EQ("BarBaz", GetEnumValueName("Foo", "FOO_BAR_BAZ", &options));
  EXPECT_EQ("BarBaz", GetEnumValueName("Foo", "Foo_BarBaz", &options));
  EXPECT_EQ("Bar", GetEnumValueName("FO_O", "FOO_BAR", &options));
  EXPECT_EQ("Bar", GetEnumValueName("FOO", "F_O_O_BAR", &options));
  EXPECT_EQ("Bar", GetEnumValueName("Foo", "BAR", &options));
  EXPECT_EQ("BarBaz", GetEnumValueName("Foo", "BAR_BAZ", &options));
  EXPECT_EQ("Foo", GetEnumValueName("Foo", "FOO", &options));
  EXPECT_EQ("Foo", GetEnumValueName("Foo", "FOO___", &options));
  // Identifiers can't start with digits
  EXPECT_EQ("_2Bar", GetEnumValueName("Foo", "FOO_2_BAR", &options));
  EXPECT_EQ("_2", GetEnumValueName("Foo", "FOO___2", &options));
  // Preserve requested enum
  EXPECT_EQ("FOO", GetEnumValueName("Bar", "FOO", &options));
  EXPECT_EQ("FOO_BAR", GetEnumValueName("Bar", "FOO_BAR", &options));
}

}  // namespace
}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
