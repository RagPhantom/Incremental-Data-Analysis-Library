# Note
Each project directory builds upon the previous one; therefore, the project5 directory contains the most recent and complete version of all files.
# Incremental-Data-Analysis-Library
- Designed and built a multi-phase C++ library across 4 iterative projects, evolving from a single time series class with dynamic resizing to a full country-level dataset supporting hundreds of time series per country
- Implemented a binary interval tree to partition countries by data mean, supporting range queries, country deletion, and path tracing with logarithmic average depth
- Built a double-hashing lookup system with tombstone deletion and periodic rehashing (CLEAN), achieving O(1) average-case country retrieval within the project's 512-slot table design