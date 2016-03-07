void checkPots(){
	// read all potentiometers, adjust values
	velocity = map(analogRead(speedPot),0,1023,0,255);
	gayness = map(analogRead(gayPot),0,1023,0,360);
	hue = map(analogRead(huePot),0,1023,0,255);
	wildness = map(analogRead(wildPot),0,1023,0,255);
}
	

