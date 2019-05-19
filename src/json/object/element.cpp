namespace JsonStreamAnalyzer {
    class Element {
    public:
        Element(int type, void *data) {
            this->type = type;
            this->data = data;
        }

    private:
        int type;
        void *data;
    };
} // JsonStreamAnalyzer
