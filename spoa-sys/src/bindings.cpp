#include <vector>

#include "spoa-sys/include/bindings.hpp"
#include "spoa-sys/src/lib.rs.h"

namespace spoa {

std::unique_ptr<AlignmentEngine>
create_alignment_engine(AlignmentType typ, std::int8_t m, std::int8_t n,
                        std::int8_t g, std::int8_t e, std::int8_t q,
                        std::int8_t c) {
  return AlignmentEngine::Create(typ, m, n, g, e, q, c);
}

std::unique_ptr<Alignment> align(AlignmentEngine &engine, const char *sequence,
                                 std::uint32_t sequence_len,
                                 const Graph &graph) {
  Alignment alignment = engine.Align(sequence, sequence_len, graph);
  return std::unique_ptr<Alignment>(new Alignment(std::move(alignment)));
}

std::unique_ptr<Graph> create_graph() {
  return std::unique_ptr<Graph>(new Graph());
}

void add_alignment(Graph &graph, const Alignment &alignment,
                   const char *sequence, std::uint32_t sequence_len,
                   const char *quality, std::uint32_t quality_len) {
  graph.AddAlignment(alignment, sequence, sequence_len, quality, quality_len);
}

std::unique_ptr<std::string> generate_consensus(Graph &graph) {
  std::string consensus = graph.GenerateConsensus();
  return std::unique_ptr<std::string>(new std::string(std::move(consensus)));
}

ConsensusQ generate_consensus_with_quality(spoa::Graph &graph) {
  auto [consensus, quality] = graph.GenerateConsensusWithQuality(0);
  return spoa::ConsensusQ {
    std::move(consensus), std::move(quality)
  };
}

std::unique_ptr<std::vector<std::string>>
generate_multiple_sequence_alignment(Graph &graph, bool include_consensus) {
  std::vector<std::string> msa =
      graph.GenerateMultipleSequenceAlignment(include_consensus);
  return std::unique_ptr<std::vector<std::string>>(
      new std::vector<std::string>(std::move(msa)));
}

} // namespace spoa
