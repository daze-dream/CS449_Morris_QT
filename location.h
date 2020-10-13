#ifndef LOCATION_H
#define LOCATION_H

//Code contributed by Jashandeep


class Location
{
public:
    Location();
    void setOccupied(bool &o){ occupied = o;}
    void setMill(bool &m) { mill = m;}

    bool isOccupied(){ return occupied; }
    bool isMill() { return mill;}
private:
    bool occupied;
    bool mill;
};

#endif // LOCATION_H
