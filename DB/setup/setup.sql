-- Locations Table
CREATE TABLE Locations (
    LocationID INT AUTO_INCREMENT PRIMARY KEY,
    LocationName VARCHAR(100) NOT NULL,
    Country VARCHAR(50),
    City VARCHAR(50),
    Address VARCHAR(200),
    PostalCode VARCHAR(20),
    Latitude DECIMAL(10, 8),
    Longitude DECIMAL(11, 8)
);

-- Hotels Table
CREATE TABLE Hotels (
    HotelID INT AUTO_INCREMENT PRIMARY KEY,
    HotelName VARCHAR(100) NOT NULL,
    LocationID INT,
    StarRating DECIMAL(3, 2),
    Description TEXT,
    ContactNumber VARCHAR(20),
    Email VARCHAR(100),
    Website VARCHAR(100),
    CheckInTime TIME,
    CheckOutTime TIME,
    FOREIGN KEY (LocationID) REFERENCES Locations(LocationID)
);

-- Rooms Table
CREATE TABLE Rooms (
    RoomID INT AUTO_INCREMENT PRIMARY KEY,
    HotelID INT,
    RoomNumber INT NOT NULL,
    RoomType VARCHAR(50) NOT NULL,
    BedType VARCHAR(50),
    MaxOccupancy INT,
    Price DECIMAL(10, 2),
    IsBooked BOOLEAN,
    Description TEXT,
    FOREIGN KEY (HotelID) REFERENCES Hotels(HotelID)
);

-- RoomImages Table
CREATE TABLE RoomImages (
    ImageID INT AUTO_INCREMENT PRIMARY KEY,
    RoomID INT,
    ImageURL VARCHAR(200),
    FOREIGN KEY (RoomID) REFERENCES Rooms(RoomID)
);

-- Amenities Table
CREATE TABLE Amenities (
    AmenityID INT AUTO_INCREMENT PRIMARY KEY,
    AmenityName VARCHAR(100) NOT NULL,
    Description TEXT,
    Category VARCHAR(50),
    Cost DECIMAL(10, 2),
    IsChargeable BOOLEAN
);

-- HotelAmenities Table
CREATE TABLE HotelAmenities (
    HotelAmenityID INT AUTO_INCREMENT PRIMARY KEY,
    HotelID INT,
    AmenityID INT,
    FOREIGN KEY (HotelID) REFERENCES Hotels(HotelID),
    FOREIGN KEY (AmenityID) REFERENCES Amenities(AmenityID)
);

-- Customers Table
CREATE TABLE Customers (
    CustomerID INT AUTO_INCREMENT PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL,
    Phone VARCHAR(20),
    Address VARCHAR(200),
    DateOfBirth DATE
);

-- Reservations Table
CREATE TABLE Reservations (
    ReservationID INT AUTO_INCREMENT PRIMARY KEY,
    CustomerID INT,
    CheckInDate DATE,
    CheckOutDate DATE,
    TotalAmount DECIMAL(10, 2),
    ReservationDate DATE,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);

-- RoomReservations Table
CREATE TABLE RoomReservations (
    RoomReservationID INT AUTO_INCREMENT PRIMARY KEY,
    ReservationID INT,
    RoomID INT,
    FOREIGN KEY (ReservationID) REFERENCES Reservations(ReservationID),
    FOREIGN KEY (RoomID) REFERENCES Rooms(RoomID)
);

-- Payments Table
CREATE TABLE Payments (
    PaymentID INT AUTO_INCREMENT PRIMARY KEY,
    ReservationID INT,
    PaymentDate DATE,
    Amount DECIMAL(10, 2),
    PaymentMethod VARCHAR(50),
    FOREIGN KEY (ReservationID) REFERENCES Reservations(ReservationID)
);

-- Reviews Table
CREATE TABLE Reviews (
    ReviewID INT AUTO_INCREMENT PRIMARY KEY,
    HotelID INT,
    CustomerID INT,
    Rating INT,
    Comment TEXT,
    ReviewDate DATE,
    FOREIGN KEY (HotelID) REFERENCES Hotels(HotelID),
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);

-- RoomReviews Table
CREATE TABLE RoomReviews (
    RoomReviewID INT AUTO_INCREMENT PRIMARY KEY,
    ReviewID INT,
    RoomID INT,
    FOREIGN KEY (ReviewID) REFERENCES Reviews(ReviewID),
    FOREIGN KEY (RoomID) REFERENCES Rooms(RoomID)
);

-- Promotions Table
CREATE TABLE Promotions (
    PromotionID INT AUTO_INCREMENT PRIMARY KEY,
    HotelID INT,
    PromotionName VARCHAR(100),
    Description TEXT,
    DiscountPercentage DECIMAL(5, 2),
    StartDate DATE,
    EndDate DATE,
    IsCouponCodeRequired BOOLEAN,
    CouponCode VARCHAR(20),
    FOREIGN KEY (HotelID) REFERENCES Hotels(HotelID)
);

-- Employees Table
CREATE TABLE Employees (
    EmployeeID INT AUTO_INCREMENT PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL,
    Phone VARCHAR(20),
    Position VARCHAR(50),
    HotelID INT,
    FOREIGN KEY (HotelID) REFERENCES Hotels(HotelID)
);

-- Events Table
CREATE TABLE Events (
    EventID INT AUTO_INCREMENT PRIMARY KEY,
    HotelID INT,
    EventName VARCHAR(100) NOT NULL,
    Description TEXT,
    EventDate DATE,
    StartTime TIME,
    EndTime TIME,
    MaxCapacity INT,
    RegistrationURL VARCHAR(200),
    FOREIGN KEY (HotelID) REFERENCES Hotels(HotelID)
);
