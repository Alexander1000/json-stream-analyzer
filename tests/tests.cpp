#include <json-stream-analyzer.h>
#include <io-buffer.h>

int main(int argc, char** argv) {
    IOBuffer::IOFileReader file_buffer("../fixtures/001-simple-example.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();
    return 0;
}
