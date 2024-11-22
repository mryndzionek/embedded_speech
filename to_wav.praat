form Test command line calls
    integer Number ???
    sentence Text ???
endform

synth = Create SpeechSynthesizer: "English (Great Britain)", "Female2"
To Sound: text$, 0
Scale peak: 0.99
Save as WAV file: "data/" + string$(number) + ".wav"

