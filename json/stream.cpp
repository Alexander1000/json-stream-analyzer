class Stream
{
public:
    Stream(IOReader* reader)
    {
        this->reader = reader;

        this->currentBuffer = new char[STREAM_BUFFER_SIZE];
        this->forwardBuffer = new char[STREAM_BUFFER_SIZE];

        memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
        memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));

        this->currentPosition = 0;

        // признак того что достигнут конец файла
        bool eof = false;
        // позиция в буфере
        this->posCurrent = 0;
        this->posForward = 0;
        this->read_size = 0;

        this->currentLine = 0;
        this->currentColumn = 0;

        this->mode = PLAIN_MODE;
    }

    ~Stream()
    {
        delete this->currentBuffer;
        delete this->forwardBuffer;
    }

    void get_next_token()
    {
        if (this->eof) {
            // достигнут конец
            return;
        }

        bool eof = false;

        if (this->currentPosition == 0 && this->read_size == 0) {
            // первый раз тут, читаем данные
            this->read_size = this->reader->read(this->currentBuffer, STREAM_BUFFER_SIZE);
            // позиция в буфере
            this->posCurrent = this->read_size;
            this->posForward = 0;

            if (this->read_size < STREAM_BUFFER_SIZE) {
                eof = true;
            } else {
                this->posForward = this->reader->read(this->forwardBuffer, STREAM_BUFFER_SIZE);
                if (this->posForward < STREAM_BUFFER_SIZE) {
                    eof = true;
                }
            }
        }

        bool endOfToken = false;
        this->eof = eof;
        this->lexemeWriter = NULL;
        bool escape = false;

        while (!endOfToken) {
            // если текущий указатель перешел в forward-буфер
            if (this->currentPosition >= STREAM_BUFFER_SIZE && this->currentPosition < 2 * STREAM_BUFFER_SIZE) {
                // очищаем буфер со старыми данными
                memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
                // копируем данные из forward buffer в current
                memcpy(this->currentBuffer, this->forwardBuffer, STREAM_BUFFER_SIZE);
                // копируме конечную позицию в буфере из forward в current
                this->posCurrent = this->posForward;
                // смещаем текущую позицию
                this->currentPosition -= STREAM_BUFFER_SIZE;
                // подготавливаем память для заливки новых данных
                memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));

                if (!eof) {
                    // если не был достигнут конец файла, читаем новый forward-буфер
                    this->posForward = this->reader->read(this->forwardBuffer, STREAM_BUFFER_SIZE);

                    if (this->posForward < STREAM_BUFFER_SIZE) {
                        eof = true;
                    }
                } else {
                    // если конец файла, то освобождаем память от forward-буфера
                    this->posForward = 0;
                }
            }

            if (this->currentPosition >= 0 && this->currentPosition < STREAM_BUFFER_SIZE) {
                // текущий указатель находится внутри первого буфера
                while (this->currentPosition < this->posCurrent) {
                    // продвигаемся по буферу вперед
                    char symbol = this->currentBuffer[this->currentPosition];
                    // this->proceedSymbol(symbol);

                    if (this->mode == PLAIN_MODE) {
                        if (symbol == '{') {
                            this->appendCurrentLexeme(symbol);
                            endOfToken = true;
                            this->mode = OBJECT_MODE;
                        }
                    }

                    if (this->mode == OBJECT_MODE) {
                        if (symbol == '"') {
                            this->appendCurrentLexeme(symbol);
                            endOfToken = true;
                            this->mode = TEXT_MODE;
                            escape = false;
                        }
                    }

                    if (this->mode == TEXT_MODE) {
                        if (symbol == '\\' && !escape) {
                            escape = true;
                        } else {
                            if (symbol == '"' && !escape) {
                                endOfToken = true;
                                this->mode = OBJECT_MODE;
                            } else {
                                this->appendCurrentLexeme(symbol);
                            }
                            escape = false;
                        }
                    }

                    // координаты токена
                    if (symbol == 0x0A) {
                        this->currentColumn = 0;
                        ++this->currentLine;
                    } else {
                        ++this->currentColumn;
                    }

                    ++this->currentPosition;
                }
            }

            if (this->currentPosition < 0 || this->currentPosition >= 2 * LEXER_BUFFER_SIZE) {
                // невалидная позиция - выход из цыкла
                this->eof = true;
                endOfToken = true;
            }
        }
    }

private:
    IOReader* reader;

    char* currentBuffer;
    char* forwardBuffer;

    // текущая позиция для чтения
    int currentPosition;

    // позиция начала текущего блока
    int posCurrent;
    // позиция начала следующего блока
    int posForward;

    // признак конца потока
    bool eof;

    int read_size;

    // координаты токена в документе
    int currentLine;
    int currentColumn;

    IOMemoryBuffer* lexemeWriter;

    int mode;

    void appendCurrentLexeme(char symbol)
    {
        if (this->lexemeWriter == NULL) {
            this->lexemeWriter = new IOMemoryBuffer;
        }

        this->lexemeWriter->write(&symbol, 1);
    }
};