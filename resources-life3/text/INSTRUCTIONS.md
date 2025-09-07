# Recording Instructions for the Artist

1. Getting Kate's voice (if you need it for your other laptop)

System Settings -> Accessibility -> Spoken Content

Download and choose Kate or Kate (Enhanced)

2. Create a file for the text

Put your Haiku in a file that looks like this, copying your text into the middle :

```
<speak version="1.1">
<prosody volume="+8dB">

Your text here.

</prosody>
</speak>
```

I've attached an example that shows some of the things you can do to change pitch, speed, and volume and to add silences. You may have to play with the words, punctuation, and spelling. You might want the whole file louder - we never settled on what matched your other files.

3. Play the text file 

In your Finder window on the directory where your xml file is, right click on the folder in the breadcrumb menu on the bottom and select "Open in Terminal":


This opens your terminal at the location where your text file exists. Now, you should be able to run this at the command line:

```
say -f text-instructions.xml
```

where the name of the file you want to play follows "-f". If you want to slow the whole file down a little, I was usually setting the rate to 135 words per minute like this:

```
say -f text-instructions.xml -r 135
```

Keep editing the file and playing it until you're happy with how it sounds.

3. Save the file to *.aiff format

Once you're happy with how it sounds, save the file like this:

```
say -f text-instructions.xml -r 135 -o text-instructions.aiff
```

You should now have an aiff file that can be played on your system.

4. Convert the file to a *.wav format

From the command line, convert the file to a wav:

```
afconvert -f WAVE -d LEI16 text-instructions.aiff ../wav/text-instructions.wav
```

