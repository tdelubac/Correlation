#ifndef DEF_QPOINT
#define DEF_QPOINT

class QPoint
{
public:
    double ind;
    double x;
    double y;
    double z;
    double val;
    double weight;
    double sample;
    QPoint(double ind, double x, double y, double z, double val, double weight, double sample) : ind(ind), x(x), y(y), z(z), val(val), weight(weight), sample(sample) {}
};

// Everythin below is required to make the class QPoint compliant with boost library rules for point object.
namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            // Adapt QPoint to Boost.Geometry

            template<> struct tag<QPoint>
            { typedef point_tag type; };

            template<> struct coordinate_type<QPoint>
            //{ typedef QPoint::double type; };
            { typedef double type; };

            template<> struct coordinate_system<QPoint>
            { typedef cs::cartesian type; };

            template<> struct dimension<QPoint> : boost::mpl::int_<3> {};

            template<>
            struct access<QPoint, 0>
            {
                //static QPoint::double get(QPoint const& p)
                static double get(QPoint const& p)
                {
                    return p.x;
                }

                //static void set(QPoint& p, QPoint::double const& value)
                static void set(QPoint& p, double const& value)
                {
                    p.x = value;
                }
            };

            template<>
            struct access<QPoint, 1>
            {
                //static QPoint::double get(QPoint const& p)
                static double get(QPoint const& p)
                {
                    return p.y;
                }

                //static void set(QPoint& p, QPoint::double const& value)
                static void set(QPoint& p, double const& value)
                {
                    p.y = value;
                }
            };

            template<>
            struct access<QPoint, 2>
            {
                //static QPoint::double get(QPoint const& p)
                static double get(QPoint const& p)
                {
                    return p.z;
                }

                //static void set(QPoint& p, QPoint::double const& value)
                static void set(QPoint& p, double const& value)
                {
                    p.z = value;
                }
            };
        }
    }
} // namespace boost::geometry::traits

#endif
