# json-stream-analyzer

Project requirements (static lib):
  - [io-buffer](https://github.com/Alexander1000/io-buffer)
  - [cpp-unit-test](https://github.com/Alexander1000/cpp-unit-test) (for tests)
  
## How use it:

Example input json (etc/config.json):
```json
{
  "host": "127.0.0.1",
  "port": 8080
}
```

Example code:
```c++
#include <iostream>
#include <string>
#include <io-buffer.h>
#include <json-stream-analyzer.h>

typedef std::map<std::string, JsonStreamAnalyzer::Element *> JsonObject;

int main(int argc, char** argv) {
    IOBuffer::IOFileReader fileReader("etc/config.json");
    IOBuffer::CharStream charStream(&fileReader);
    JsonStreamAnalyzer::Stream stream(&charStream);
    JsonStreamAnalyzer::Decoder decoder(&stream);
    
    JsonStreamAnalyzer::Element* element = decoder.decode();
    
    if (element->getType() == ELEMENT_TYPE_OBJECT) {
        JsonObject* obj = (JsonObject*) element->getData();
        if (obj->find("host") != obj->end()) {
            JsonStreamAnalyzer::Element* elHost = obj->at("host");
            if (elHost->getType() == ELEMENT_TYPE_TEXT) {
                std::cout << (std::string*) elHost->getData() << std::endl;
            }
        }

        if (obj->find("port") != obj->end()) {
            JsonStreamAnalyzer::Element* elPort = obj->at("port");
            if (elPort->getType() == ELEMENT_TYPE_NUMERIC) {
                std::cout << (std::string*) elPort->getData() << std::endl;
            }
        }
    }
        
    return 0;
}
```

## How build:
```shell
cmake .
make
```

## How tests:
```shell
cd tests
./test.sh
```
