^ this is the music note A Major expressed in Phonon with a saw wave ^

void mainAudio$(out float a, in float t) {

	^ saw() produces the saw wave shape: ^
	^ t = 439; a = 439.0; ^
	^ t = 440.0; a = 0.0; ^
	a = saw$(t*440.0);
	print$("this is a string!");


	4$
}