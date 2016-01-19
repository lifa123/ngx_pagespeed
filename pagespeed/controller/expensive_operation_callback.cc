// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: cheesy@google.com (Steve Hill)

#include "pagespeed/controller/expensive_operation_callback.h"

namespace net_instaweb {

ExpensiveOperationContext::ExpensiveOperationContext(
    CentralControllerInterface* central_controller)
    : central_controller_(central_controller) {
}

ExpensiveOperationContext::~ExpensiveOperationContext() {
  Done();
}

void ExpensiveOperationContext::Done() {
  if (central_controller_ != NULL) {
    central_controller_->NotifyExpensiveOperationComplete();
    central_controller_ = NULL;
  }
}

ExpensiveOperationCallback::ExpensiveOperationCallback(
    Sequence* sequence)
    : CentralControllerCallback<ExpensiveOperationContext>(sequence) {
}

ExpensiveOperationCallback::~ExpensiveOperationCallback() {
}

ExpensiveOperationContext* ExpensiveOperationCallback::CreateTransactionContext(
    CentralControllerInterface* interface) {
  return new ExpensiveOperationContext(interface);
}

}  // namespace net_instaweb
