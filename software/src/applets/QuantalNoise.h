// Copyright (c) 2018, Jason Justian
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

class QuantalNoise : public HemisphereApplet {
public:

    const char* applet_name() { // Maximum 10 characters
        return "QuantNoise";
    }
    const uint8_t* applet_icon() { return PhzIcons::trigseq; }

    void Start() {
        ForEachChannel(ch) {
            Out(ch, 0);
        }
        counter = 0;
    }

    void Controller() {
        ForEachChannel(ch) {
            if (Clock(ch)) {
                cv[ch] = round(values[counter] * 5 * (12 << 7));
                Out(ch, cv[ch]);

                counter += 1;
                if (counter >= numValues) counter = 0;

            }

        }
    }

    void View() {
        gfxHeader(applet_name());
        gfxSkyline();
    }

    void OnButtonPress() {
    }

    void OnEncoderMove(int direction) {
    }

    uint64_t OnDataRequest() {
        uint64_t data = 0;
        return data;
    }

    void OnDataReceive(uint64_t data) {
    }

protected:
    void SetHelp() {
        //                    "-------" <-- Label size guide
        help[HELP_DIGITAL1] = "Clock";
        help[HELP_DIGITAL2] = "Reset";
        help[HELP_CV1]      = "Swap Ch";
        help[HELP_CV2]      = "Offset";
        help[HELP_OUT1]     = "Trg Ch1";
        help[HELP_OUT2]     = "Trg Ch2";
        help[HELP_EXTRA1] = "";
        help[HELP_EXTRA2] = "";
       //                   "---------------------" <-- Extra text size guide
    }

private:
    float values[10] = {0.0, 0.9, 0.83, 0.94, 0.45, 0.78, 0.99, 0.87, 1.0, 0.93};
    //{128, 243, 234, 248, 186, 228, 254, 239, 255, 247}
    uint8_t numValues = 10;
    int cv[2];
    uint8_t counter = 0;

};
