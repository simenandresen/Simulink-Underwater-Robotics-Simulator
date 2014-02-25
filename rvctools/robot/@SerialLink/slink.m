function sl = slink(l)

    sl = Link(l);   % clone the link

    if sl.alpha == pi/2
        sl.alpha = sym('pi/2');
    end
    if sl.alpha == -pi/2
        sl.alpha = sym('-pi/2');
    end
    if sl.alpha == pi
        sl.alpha = sym('pi');
    end
    if sl.alpha == -pi
        sl.alpha = sym('-pi');
    end

    if l.isprismatic
        if sl.alpha == pi/2
            sl.alpha = sym('pi/2');
        end
        if sl.alpha == -pi/2
            sl.alpha = sym('-pi/2');
        end
        if sl.alpha == pi
            sl.alpha = sym('pi');
        end
        if sl.alpha == -pi
            sl.alpha = sym('-pi');
        end
    end
