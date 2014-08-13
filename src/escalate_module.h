/**
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ESCALATE_MODULE_H_
#define ESCALATE_MODULE_H_

#define ESCALATE_MODULE_ERROR _EscalateModuleErrorQuark()

#include "escalate_subprocess.h"

#include <glib.h>
#include <security/pam_modules.h>

typedef enum {
  ESCALATE_MODULE_ERROR_UNKNOWN_ARG = 1,
  ESCALATE_MODULE_ERROR_NO_USERNAME,
  ESCALATE_MODULE_ERROR_GET_ITEM_FAILED,
  ESCALATE_MODULE_ERROR_CONV,
  ESCALATE_MODULE_ERROR_MESSAGE_TYPE,
} EscalateModuleError;

typedef struct {
  pam_handle_t *pamh;
  int flags;
  gchar *username;
  gboolean use_first_pass;
  gboolean try_first_pass;
  struct pam_conv *conv;
  EscalateSubprocess *child;
  gboolean keep_going;
  int result;
} EscalateModule;

EscalateModule *EscalateModuleNew(pam_handle_t *pamh, int flags, int argc,
                                  const char **argv, GError **error);
void EscalateModuleFree(EscalateModule *self);

gboolean EscalateModuleStart(EscalateModule *self, EscalateMessageAction action,
                             GError **error);
gboolean EscalateModuleHandleNext(EscalateModule *self, GError **error);
gboolean EscalateModuleKeepGoing(EscalateModule *self);
int EscalateModuleGetResult(EscalateModule *self);

GQuark _EscalateModuleErrorQuark();

#endif