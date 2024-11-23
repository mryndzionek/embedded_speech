form Test command line calls
    integer Number ???
endform

Read from file: "data/" + string$(number) + ".wav"
Scale peak: 0.99
Scale intensity: 65.0
Resample: 4000, 50
To LPC (burg)... 8 0.1 0.05 60.0
Save as text file: "data/" + string$(number) + ".LPC"

