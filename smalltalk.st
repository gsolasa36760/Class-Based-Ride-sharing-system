Object subclass: Ride [
    | id from to miles |

    Ride class >> create: rideID from: start to: end distance: dist [
        ^ self new setup: rideID from: start to: end distance: dist
    ]

    setup: rideID from: start to: end distance: dist [
        id := rideID.
        from := start.
        to := end.
        miles := dist.
    ]

    fare [ ^ 0 ]  "Base"

    showDetails [
        Transcript show: 'Ride ID: ', id; cr.
        Transcript show: 'From: ', from, ' To: ', to; cr.
        Transcript show: 'Miles: ', miles printString; cr.
        Transcript show: 'Fare: $', (self fare) printString; cr.
    ]
]

Ride subclass: StandardRide [
    fare [ ^ 3.0 + (1.1 * miles) ]
]

Ride subclass: PremiumRide [
    fare [ ^ 6.0 + (2.3 * miles) ]
]

Object subclass: Driver [
    | id name rating rideList |

    Driver class >> withID: dID name: n rating: r [
        ^ self new initializeWithID: dID name: n rating: r
    ]

    initializeWithID: dID name: n rating: r [
        id := dID.
        name := n.
        rating := r.
        rideList := OrderedCollection new.
    ]

    addRide: ride [
        rideList add: ride.
    ]

    summary [
        Transcript show: 'Driver: ', name, ' (', id, ')'; cr.
        Transcript show: 'Rating: ', rating printString; cr.
        Transcript show: 'Rides Completed: ', rideList size printString; cr.
    ]
]

Object subclass: Rider [
    | id name history |

    Rider class >> withID: rID name: n [
        ^ self new initWithID: rID name: n
    ]

    initWithID: rID name: n [
        id := rID.
        name := n.
        history := OrderedCollection new.
    ]

    bookRide: ride [
        history add: ride.
    ]

    rideHistory [
        Transcript show: 'Rider: ', name, ' (', id, ')'; cr.
        Transcript show: 'Past Rides:'; cr.
        history do: [:ride | ride showDetails. Transcript show: '--------'; cr].
    ]
]

"--- Example Execution ---"
| driver rider r1 r2 |

r1 := StandardRide create: 'RID300' from: 'Central Park' to: 'Harbor Point' distance: 4.2.
r2 := PremiumRide create: 'RID301' from: 'Stadium' to: 'Art Gallery' distance: 7.5.

driver := Driver withID: 'DRV900' name: 'Nathaniel' rating: 4.6.
driver addRide: r1.
driver addRide: r2.

rider := Rider withID: 'USR800' name: 'Sophia'.
rider bookRide: r1.
rider bookRide: r2.

driver summary.
Transcript cr.
rider rideHistory.
