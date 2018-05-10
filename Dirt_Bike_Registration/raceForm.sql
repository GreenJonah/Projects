#Create the database
CREATE DATABASE raceForm;

#Connect to the database
\c raceform


# Bikes Table
CREATE TABLE public.bikes (
	id SERIAL NOT NULL PRIMARY KEY,
	bike_type VARCHAR(10)	
);

# Races Table
CREATE TABLE public.terrain (
	id SERIAL NOT NULL PRIMARY KEY,
	terrain_type VARCHAR(50)
);

# Racers table
CREATE TABLE public.racers(
	id SERIAL NOT NULL PRIMARY KEY,
	firstName VARCHAR(50) NOT NULL,
	lastName  VARCHAR(50) NOT NULL,
	password  VARCHAR(255) NOT NULL,
	email     VARCHAR(80) UNIQUE NOT NULL,
	terrain_id  INT NOT NULL REFERENCES public.terrain(id),
	bikes_id  INT NOT NULL REFERENCES public.bikes(id)
);