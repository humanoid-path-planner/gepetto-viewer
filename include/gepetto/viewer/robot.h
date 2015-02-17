#ifndef OSGROBOT_H
#define OSGROBOT_H


#include <urdf_model/model.h>
#include <osg/MatrixTransform>
namespace se3
{
class Model;
}
namespace graphics
{
class Link:public osg::Group
{
protected:
    boost::shared_ptr<urdf::Link > _urdfmodel;
public:
    Link(): osg::Group() {}
    Link(boost::shared_ptr<urdf::Link >&l) :osg::Group()
    {
        _urdfmodel=l;
    }
    Link(const Link&rhs)
    {
        this->_urdfmodel=rhs._urdfmodel;
    }


    Link(const Link&rhs,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY):osg::Group(rhs,  copyop) {}
    META_Node(graphics, Link);

    ///Properties
    inline const urdf::Link *getUrdfModel()const
    {
        return _urdfmodel.get() ;
    }
    inline void setUrdfModel(boost::shared_ptr<urdf::Link > &l)
    {
        _urdfmodel=l ;
    }
};


class Joint:public osg::MatrixTransform
{
protected:
    boost::shared_ptr<urdf::Joint > _urdfmodel;
public:
    Joint() :osg::MatrixTransform(){    }
    Joint(boost::shared_ptr<urdf::Joint >&l) :osg::MatrixTransform()
    {
        _urdfmodel=l;
    }
    Joint(const Joint&rhs)
    {
        this->_urdfmodel=rhs._urdfmodel;
    }

    Joint(const Joint&rhs,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY):osg::MatrixTransform(rhs,  copyop) {}
    META_Node(graphics, Joint);
    ///Properties
    inline const urdf::Joint *getUrdfModel()const
    {
        return _urdfmodel.get() ;
    }
    inline void setUrdfModel(boost::shared_ptr<urdf::Joint >&l)
    {
        _urdfmodel=l ;
    }
};

class Robot:public osg::Group
{

public:

    Robot();

    Robot(const Robot&rhs,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY) :osg::Group(rhs,  copyop) {}
    META_Node(graphics, Robot);

    se3::Model * getSE3Model()const
    {
        return SE3Model;
    }

    void setUrdfPackageRootDirectory(const std::string & s)
    {
        _urdfPackageRootDirectory=s;
    }
    const std::string & getUrdfPackageRootDirectory()const
    {
        return _urdfPackageRootDirectory ;
    }


    void addLink(boost::shared_ptr<urdf::Link > &link)
    {
        parse(link);
    }
    void addJoint(boost::shared_ptr<urdf::Joint > &link)
    {
        parse(link);
    }
    Joint *getOsgJoint(boost::shared_ptr<urdf::Joint >j) ;
    Link *getOsgLink(boost::shared_ptr<urdf::Link >j);


protected:
    ///Meshes loading
    virtual bool parse (boost::shared_ptr<urdf::Link > &link);
    ///SE3Model.addBody (if DOF) + osg::Transform creation
    virtual bool  parse (boost::shared_ptr<urdf::Joint > &link);
    ~Robot();
    osg::ref_ptr<osg::Node> _debugaxes; ///
    std::string _urdfPackageRootDirectory;
    se3::Model *SE3Model;

protected:
    ///classic async model
    ///typedef std::tuple<urdf::Model *,osg::Model,SE3::Model,...> ModelstoSync
    ///choice done: urdf as entry point and maintain with dirtyflag and use osg update callback to sync models
    ///store local reference to joint and link for direct memory access
    /// inner indexes
    typedef unsigned int LinkIndex;
    typedef unsigned int JointIndex;
    std::vector<boost::shared_ptr<urdf::Link > > _links;
    std::vector<osg::ref_ptr<Link > > _osglinks;
    std::map< urdf::Link *,LinkIndex  > _invLinksMap;

    std::vector<boost::shared_ptr<urdf::Joint > > _joints;
    std::vector<osg::ref_ptr<Joint > > _osgjoints;
    std::map< urdf::Joint *,JointIndex  > _invJointsMap;

};
}
#endif
