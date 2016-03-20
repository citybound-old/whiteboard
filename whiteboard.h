namespace wb {
    struct color {
        float r, g, b, a;
    };

    class draw_stream {
    public:
        draw_stream(std::ostream& out) : out(out) {};

        draw_stream& operator<< (draw_stream &(* manipulator)(draw_stream &)) {
            return manipulator(*this);
        }

        void lineDone () {
            out << std::endl;
            wrotePrefix = false;
        }

        void clear () {
            out << std::endl;
            out << "Whiteboard: ----" << std::endl;
            wrotePrefix = false;
        }

        std::ostream& startOutput() {
            if (!wrotePrefix) {
                out << "Whiteboard: ";
                wrotePrefix = true;
            }

            return out;
        }
    private:
        std::ostream& out;
        bool wrotePrefix = false;
    };

    draw_stream draw (std::ostream& out) {
        return draw_stream(out);
    }

    draw_stream& clear (draw_stream& draw_stream) {
        draw_stream.clear();
        return draw_stream;
    }

}

wb::draw_stream& operator<< (wb::draw_stream& drawStream, wb::color c) {
    drawStream.startOutput() << "color " << c.r << " " << c.g << " " << c.b << " " << c.a;
    drawStream.lineDone();
    return drawStream;
}