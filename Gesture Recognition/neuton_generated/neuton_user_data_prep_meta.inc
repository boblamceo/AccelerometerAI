/* 2024-08-13T10:14:31Z */

/* ----------------------------------------------------------------------
Copyright (c) 2022-2023 Neuton.AI, Inc.
*
The source code and its binary form are being made available on the following terms:
Redistribution, use, and modification are permitted provided that the following
conditions are met:
*
1. Redistributions of source code and/or its binary form must retain the above copyright notice,
* this list of conditions (and the disclaimer) either in the body of the source code or in
* the documentation and/or other materials provided with the distribution of the binary form, as
applicable.
*
2. The name of the copyright holder may not be used to endorse or promote products derived from this
* source code or its binary form without specific prior written permission of Neuton.AI, Inc.
*
3. Disclaimer. THIS SOURCE CODE AND ITS BINARY FORM ARE PROVIDED BY THE COPYRIGHT HOLDER "AS IS".
* THE COPYRIGHT HOLDER HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS
* OF THIRD PARTIES; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE OR ITS BINARY FORM, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------- */

/** Defines input(also used for LAG) features MIN scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MIN[] = { -13, 0, -13, -4, -4,
     -3, -11, 1, -14, -3, -4, -3, -10, 3, -14, -3, -3, -2, -9, 2, -10, -4, -4,
     -4, -5, -4, -12, -4, -2, -4, -10, -3, -12, -2, -3, -3, -6, -6, -10, -3,
     -2, -4, -14, -9, -8, -3, -4, -4, -11, -6, -10, -2, -2, -3, -11, -5, -10,
     -1, -1, -4, -14, -7, -11, -3, -4, -4, -4, -8, -11, -4, -3, -3, -4, -1, -9,
     -4, -2, -3, -13, 0, -11, -4, -2, -4, -7, -7, -11, -3, -4, -4, -13, 1, -11,
     -2, -3, -3, -9, 0, -11, -2, -3, -4, -8, 0, -13, -2, -2, -2, -7, 2, -10,
     -2, -3, -4, -14, 0, -12, -3, -4, -4, -10, 1, -13, -4, -3, -4, -14, -7, -15,
     -3, -3, -4, -11, 2, -11, -3, -4, -4, -7, 0, -9, -4, -3, -4, -9, -3, -10,
     -3, -3, -3, -8, 1, -14, -4, -4, -4, -6, -2, -10, -3, -3, -3, -5, 0, -9,
     -2, -3, -4, -10, -4, -9, -2, -2, -4, -6, 3, -10, -2, -2, -2, -5, 0, -11,
     -3, -1, -4, -19, -18, -10, -3, -2, -4, -10, 1, -10, -2, -2, -4, -9, -6,
     -12, -3, -4, -4, -6, -2, -11, -3, -3, -4, -8, 1, -13, -2, -3, -4, -9, 0,
     -12, -2, -4, -4, -11, 0, -12, -4, -3, -4, -8, 0, -12, -3, -2, -4, -12, 3,
     -10, -4, -3, -3, -8, 0, -10, -3, -4, -3, -7, 1, -11, -4, -3, -3, -7, 4,
     -11, -3, -3, -3, -7, -2, -10, -4, -4, -3, -8, -14, -9, -4, -4, -3, -9, -19,
     -10, -3, -3, -4, -12, -14, -12, -3, -3, -2, -12, -7, -9, -3, -2, -4, -6,
     -5, -9, -3, -3, -4, -6, 0, -9, -4, -3, -4 };

/** Defines input(also used for LAG) features MAX scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MAX[] = { 16, 18, 16, 4, 3,
     4, 12, 18, 19, 2, 4, 4, 12, 19, 19, 1, 4, 3, 14, 18, 10, 4, 2, 3, 12, 12,
     9, 3, 2, 4, 15, 12, 7, 3, 3, 4, 13, 12, 8, 3, 4, 4, 16, 14, 10, 2, 4, 2,
     19, 13, 5, 2, 2, 3, 11, 18, 8, 3, 3, 2, 13, 14, 5, 4, 4, 4, 12, 12, 1, 2,
     2, 4, 14, 12, 5, 1, 2, 4, 13, 12, 3, 3, 4, 4, 12, 16, 6, 2, 4, 3, 14, 11,
     8, 3, 4, 4, 14, 12, 7, 2, 4, 3, 14, 10, 8, 2, 4, 2, 11, 13, 9, 1, 2, 2,
     13, 16, 12, 1, 2, 1, 19, 19, 13, 4, 2, 3, 12, 15, 12, 3, 2, 4, 11, 18, 10,
     3, 3, 3, 11, 19, 17, 4, 4, 4, 19, 18, 11, 3, 3, 4, 11, 17, 14, 2, 3, 4,
     12, 18, 18, 3, 2, 4, 12, 13, 13, 3, 2, 2, 13, 13, 10, 2, 4, 3, 13, 12, 7,
     4, 4, 1, 12, 13, 7, 4, 4, 4, 19, 13, 8, 3, 3, 4, 13, 16, 9, 2, 2, 4, 12,
     11, 5, 2, 2, 3, 18, 11, 7, 2, 2, 4, 14, 13, 17, 2, 1, 3, 13, 15, 13, 2,
     3, 2, 13, 15, 12, 2, 2, 2, 14, 15, 6, 2, 2, 4, 12, 12, 6, 2, 2, 4, 13, 15,
     16, 4, 4, 4, 14, 16, 14, 3, 3, 3, 14, 16, 11, 2, 2, 2, 13, 19, 16, 3, 4,
     4, 19, 19, 11, 3, 2, 4, 12, 11, 6, 3, 3, 4, 18, 16, 8, 3, 2, 2, 12, 14,
     9, 3, 2, 4, 15, 15, 8, 4, 2, 4, 13, 14, 10, 4, 1, 4 };

