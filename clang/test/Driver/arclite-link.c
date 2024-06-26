// RUN: touch %t.o
// RUN: mkdir -p %t.tmpdir/Xcode.app/Contents/Developers/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk
// RUN: not %clang -### -target x86_64-apple-darwin10 -fobjc-link-runtime -lfoo -mmacos-version-min=10.10 %t.o \
// RUN: -isysroot %t.tmpdir/Xcode.app/Contents/Developers/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk 2>&1 | FileCheck -check-prefix=CHECK-ARCLITE-OSX %s
// RUN: %clang -### -target x86_64-apple-darwin10 -fobjc-link-runtime -mmacos-version-min=10.11 %t.o 2>&1 | FileCheck -check-prefix=CHECK-NOARCLITE %s
// RUN: %clang -### -target i386-apple-darwin10 -fobjc-link-runtime -mmacos-version-min=10.7 %t.o 2>&1 | FileCheck -check-prefix=CHECK-NOARCLITE %s
// RUN: %clang -### -target x86_64-apple-darwin10 -fobjc-link-runtime -nostdlib %t.o 2>&1 | FileCheck -check-prefix=CHECK-NOSTDLIB %s

// CHECK-ARCLITE-OSX: .tmpdir/Xcode.app/{{.*}}libarclite_macosx.a';
// CHECK-ARCLITE-OSX: try increasing the minimum deployment target
// CHECK-ARCLITE-OSX: -lfoo
// CHECK-ARCLITE-OSX: libarclite_macosx.a
// CHECK-ARCLITE-OSX: -framework
// CHECK-ARCLITE-OSX: Foundation
// CHECK-ARCLITE-OSX: -lobjc
// CHECK-NOARCLITE-NOT: libarclite
// CHECK-NOSTDLIB-NOT: -lobjc

// RUN: not %clang -### -target x86_64-apple-darwin10 -fobjc-link-runtime -fobjc-arc -mmacos-version-min=10.10 %s 2>&1 | FileCheck -check-prefix=CHECK-UNUSED %s

// CHECK-UNUSED-NOT: warning: argument unused during compilation: '-fobjc-link-runtime'

// RUN: %clang -### -target arm64e-apple-ios8 -fobjc-link-runtime %t.o 2>&1 | FileCheck -check-prefix=CHECK-ARCLITE-ARM64E %s
// CHECK-ARCLITE-ARM64E-NOT: libarclite

// RUN: %clang -### -target arm64-apple-macos10.8 -fobjc-link-runtime %t.o 2>&1 | FileCheck -check-prefix=CHECK-ARCLITE-ARM-MAC %s
// CHECK-ARCLITE-ARM-MAC-NOT: libarclite
