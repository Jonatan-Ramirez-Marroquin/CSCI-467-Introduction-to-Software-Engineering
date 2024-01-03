DROP TABLE IF EXISTS legacyDB;
DROP TABLE IF EXISTS inventoryDB;

CREATE TABLE legacyDB(
	partID INT NOT NULL AUTO_INCREMENT,
	partDescription VARCHAR(255) NOT NULL,
	partWeight DECIMAL(7,2) NOT NULL,
	partPicture VARCHAR(500) NOT NULL,
	partPrice DECIMAL(7,2) NOT NULL,
	PRIMARY KEY(partID)
);

CREATE TABLE inventoryDB(
	partID INT NOT NULL AUTO_INCREMENT,
	partName VARCHAR(255) NOT NULL,
	partInventory INT NOT NULL,
	PRIMARY KEY(partID),
	FOREIGN KEY(partID) REFERENCES legacyDB(partID)
);

INSERT INTO legacyDB (partDescription, partWeight, partPicture, partPrice)
VALUES ("Rechargeable battery used to start a motor vehicle. Quantity 1.", 35.00, "https://bit.ly/3nZQWNI", 199.95);

INSERT INTO legacyDB (partDescription, partWeight, partPicture, partPrice)
VALUES ("Electric generator used in automobiles. Quantity 1.", 25.40, "https://bit.ly/3xwzQds", 174.99);

INSERT INTO legacyDB (partDescription, partWeight, partPicture, partPrice)
VALUES ("Used to slow or stop a moving vehicle, wheel, axle. Quantity 4.", 21.50, "https://bit.ly/3E1vgX3", 154.99);

INSERT INTO legacyDB (partDescription, partWeight, partPicture, partPrice)
VALUES ("Removes heat from coolant to prevent the engine from overheating. Quantity 1.", 10.00, "https://bit.ly/3EdOQPW", 179.95);

INSERT INTO legacyDB (partDescription, partWeight, partPicture, partPrice)
VALUES ("Part of the suspension system; Link the wheels to the vehicle. Quantity 2.", 120.00, "https://bit.ly/318d3sk", 174.99);

INSERT INTO legacyDB (partDescription, partWeight, partPicture, partPrice)
VALUES ("Provides variable ratios between engine output and differential input. Quantity 1.", 226.00, "https://bit.ly/3FPs55i", 2199.99);

INSERT INTO inventoryDB (partID, partName, partInventory)
VALUES (1, "Battery", 10);

INSERT INTO inventoryDB (partID, partName, partInventory)
VALUES (2, "Alternator", 25);

INSERT INTO inventoryDB (partID, partName, partInventory)
VALUES (3, "Brakes", 5);

INSERT INTO inventoryDB (partID, partName, partInventory)
VALUES (4, "Radiator", 7);

INSERT INTO inventoryDB (partID, partName, partInventory)
VALUES (5, "Axle", 13);

INSERT INTO inventoryDB (partID, partName, partInventory)
VALUES (6, "Transmission", 2);
