#pragma once

#include "rust/cxx.h"

#include <memory>
#include <string>
#include <vector>

#include "spoa-sys/spoa/include/spoa/spoa.hpp"

namespace spoa
{
  struct ConsensusQ;
  struct AlignmentResult;

  std::unique_ptr<spoa::AlignmentEngine>
  create_alignment_engine(spoa::AlignmentType type, std::int8_t m,
                          std::int8_t n, std::int8_t g, std::int8_t e,
                          std::int8_t q, std::int8_t c);

  std::unique_ptr<spoa::Alignment> align(spoa::AlignmentEngine &engine,
                                         const char *sequence,
                                         std::uint32_t sequence_len,
                                         const Graph &graph);

  std::unique_ptr<std::string>
  alignment_engine_type(spoa::AlignmentEngine &engine);

  std::unique_ptr<spoa::Graph> create_graph();

  AlignmentResult add_alignment(spoa::Graph &graph,
                                const spoa::Alignment &alignment,
                                const char *sequence,
                                std::uint32_t sequence_len, const char *quality,
                                std::uint32_t quality_len);

  AlignmentResult predict_alignment(spoa::Graph &graph,
                                    const spoa::Alignment &alignment,
                                    const char *sequence,
                                    std::uint32_t sequence_len);

  std::unique_ptr<std::string> generate_consensus(spoa::Graph &graph);
  ConsensusQ generate_consensus_with_quality(spoa::Graph &graph);

  std::unique_ptr<std::vector<std::string>>
  generate_multiple_sequence_alignment(spoa::Graph &graph,
                                       bool include_consensus);

} // namespace spoa
