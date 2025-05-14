#[cxx::bridge(namespace = "spoa")]
pub mod ffi {
    /// Enumerates the possible alignment types
    #[repr(u32)]
    enum AlignmentType {
        /// Smith-Waterman alignment
        kSW,
        /// Needleman-Wunsch alignment
        kNW,
        /// Overlap alignment
        kOV,
    }

    #[derive(Clone, Debug)]
    struct ConsensusQ {
        pub sequence: String,
        pub quality: String,
    }

    #[derive(Copy, Clone, Debug)]
    struct AlignmentResult {
        pub new_nodes: u32,
        pub sequence_len: u32,
        pub valid_nodes: u32,
    }

    unsafe extern "C++" {
        include!("spoa-sys/include/bindings.hpp");

        type Alignment;
        type AlignmentEngine;
        type AlignmentType;
        type Graph;

        fn create_graph() -> UniquePtr<Graph>;
        /// # Safety
        /// this function is unsafe because cxx says pointer arguments are unsafe
        unsafe fn add_alignment(
            graph: Pin<&mut Graph>,
            alignment: &Alignment,
            sequence: *const c_char,
            sequence_len: u32,
            quality: *const c_char,
            quality_len: u32,
        ) -> AlignmentResult;

        fn generate_consensus(graph: Pin<&mut Graph>) -> UniquePtr<CxxString>;
        fn generate_consensus_with_quality(graph: Pin<&mut Graph>) -> ConsensusQ;
        fn generate_multiple_sequence_alignment(
            graph: Pin<&mut Graph>,
            include_consensus: bool,
        ) -> UniquePtr<CxxVector<CxxString>>;

        fn create_alignment_engine(
            typ: AlignmentType,
            m: i8,
            n: i8,
            g: i8,
            e: i8,
            q: i8,
            c: i8,
        ) -> UniquePtr<AlignmentEngine>;
        /// # Safety
        /// this function is unsafe because cxx says pointer arguments are unsafe
        unsafe fn align(
            alignment_engine: Pin<&mut AlignmentEngine>,
            sequence: *const c_char,
            sequence_len: u32,
            graph: &Graph,
        ) -> UniquePtr<Alignment>;
    }
}
