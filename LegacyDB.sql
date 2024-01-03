DROP TABLE IF EXISTS legacyDB;

CREATE TABLE legacyDB(
	partNumber INT NOT NULL AUTO_INCREMENT,
	partName VARCHAR(255) NOT NULL,
	partDescription VARCHAR(255) NOT NULL,
	partWeight DECIMAL(7,2) NOT NULL,
	partPicture VARCHAR(500) NOT NULL,
	partPrice DECIMAL(7,2) NOT NULL,
	PRIMARY KEY(partNumber)
);

INSERT INTO legacyDB (partName, partDescription, partWeight, partPicture, partPrice)
VALUES ("Battery", "Rechargeable battery used to start a motor vehicle. Quantity 1.", 35.00, "https://bit.ly/3nZQWNI", 199.95);

INSERT INTO legacyDB (partName, partDescription, partWeight, partPicture, partPrice)
VALUES ("Alternator", "Electric generator used in automobiles. Quantity 1.", 25.40, "https://bit.ly/3xwzQds", 174.99);

INSERT INTO legacyDB (partName, partDescription, partWeight, partPicture, partPrice)
VALUES ("Brakes", "Used to slow or stop a moving vehicle, wheel, axle. Quantity 4.", 21.50, "https://bit.ly/3E1vgX3", 154.99);

INSERT INTO legacyDB (partName, partDescription, partWeight, partPicture, partPrice)
VALUES ("Radiator", "Removes heat from coolant to prevent the engine from overheating. Quantity 1.", 10.00, "https://bit.ly/3EdOQPW", 179.95);

INSERT INTO legacyDB (partName, partDescription, partWeight, partPicture, partPrice)
VALUES ("Axle", "Part of the suspension system; Link the wheels to the vehicle. Quantity 2.", 120.00, "https://bit.ly/318d3sk", 174.99);

INSERT INTO legacyDB (partName, partDescription, partWeight, partPicture, partPrice)
VALUES ("Transmission", "Provides variable ratios between engine output and differential input. Quantity 1.", 226.00, "https://bit.ly/3FPs55i", 2199.99);
