#ifndef __obj_h_
#define __obj_h_

class object {
public:
    virtual object() = 0;
    virtual ~object() = 0;

    virtual void 	render() = 0;

private:

}

#endif
