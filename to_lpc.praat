form Test command line calls
    integer Number ???
endform

Read from file: "data/" + string$(number) + ".wav"
Scale peak: 0.99
Resample: 11000, 50
To LPC (burg)... 12 0.04 0.04 10.0
Save as text file: "data/" + string$(number) + ".LPC"

