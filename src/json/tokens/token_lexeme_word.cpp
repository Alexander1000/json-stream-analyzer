class TokenLexemeWord : public Token
{
public:
    TokenLexemeWord(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
//        char* buffer = new char[512];
//        reader->read(buffer, 512);
//        cout << "Token: " << buffer << endl;
    }
};
