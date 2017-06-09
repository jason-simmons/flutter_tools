/*
 * Copyright 2017 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIB_TXT_SRC_PARAGRAPH_H_
#define LIB_TXT_SRC_PARAGRAPH_H_

#include <vector>

#include "lib/ftl/macros.h"
#include "lib/txt/src/paint_record.h"
#include "lib/txt/src/paragraph_constraints.h"
#include "lib/txt/src/paragraph_style.h"
#include "lib/txt/src/styled_runs.h"
#include "minikin/LineBreaker.h"
#include "third_party/gtest/include/gtest/gtest_prod.h"
#include "third_party/skia/include/core/SkTextBlob.h"

class SkCanvas;

namespace txt {

class Paragraph {
 public:
  Paragraph();

  ~Paragraph();

  void Layout(const ParagraphConstraints& constraints,
              const std::string& rootdir = "");

  void Paint(SkCanvas* canvas, double x, double y);

  const ParagraphStyle& GetParagraphStyle() const;

  double GetHeight() const;

  bool DidExceedMaxLines() const;

 private:
  friend class ParagraphBuilder;
  FRIEND_TEST(RenderTest, SimpleParagraph);
  FRIEND_TEST(RenderTest, SimpleRedParagraph);
  FRIEND_TEST(RenderTest, RainbowParagraph);
  FRIEND_TEST(RenderTest, DefaultStyleParagraph);
  FRIEND_TEST(RenderTest, BoldParagraph);
  FRIEND_TEST(RenderTest, LinebreakParagraph);
  FRIEND_TEST(RenderTest, ItalicsParagraph);

  std::vector<uint16_t> text_;
  StyledRuns runs_;
  minikin::LineBreaker breaker_;
  std::vector<PaintRecord> records_;
  ParagraphStyle paragraph_style_;
  int lines_ = 1;      // Number of lines after Layout().
  SkScalar y_ = 0.0f;  // Height of the paragraph after Layout().

  void SetText(std::vector<uint16_t> text, StyledRuns runs);

  void SetParagraphStyle(const ParagraphStyle& style);

  void AddRunsToLineBreaker(const std::string& rootdir = "");

  FTL_DISALLOW_COPY_AND_ASSIGN(Paragraph);
};

}  // namespace txt

#endif  // LIB_TXT_SRC_PARAGRAPH_H_
