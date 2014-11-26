#!/usr/bin/env python
import lsst.pex.policy as pexPolicy
import os, math


def writeCCDPositionAsPAF(camera, ccdPositionList, output):
    """
    Write CCDPositionList in the ".paf" format.
    *N*O*T*E* this function does not output a full PAF file.
    You can manually copy and paste this output into another file,
    but you must not let this function overwrite the file.

    @param camera: "HSC" or "SC"
    @param ccdPositionList: an instance of CCDPositionList
    @param output: a file object or a path name
    """

    #
    # Load camera geometry
    #

    if camera == "HSC":
        policyFile = pexPolicy.DefaultPolicyFile("obs_subaru", "HscMapper.paf", "policy")
        policy = pexPolicy.Policy(policyFile)
    elif camera == "SC":
        policyFile = pexPolicy.DefaultPolicyFile("obs_subaru", "SuprimecamMapper.paf", "policy")
        policy = pexPolicy.Policy(policyFile)
    else:
        raise ValueError("camera is not supported: '%s'" % camera)

    cameraPath = os.path.join(
        os.path.dirname(policyFile.getPath()),
        policy.get("camera")
    )

    raft = pexPolicy.Policy(cameraPath).get("Raft")

    #
    # Update the geometry with ccdPositionList
    #

    deg = 180/math.pi

    for ccd in raft.getArray("Ccd"):
        ccdId = ccd.get("serial")
        if ccdId >= len(ccdPositionList): continue

        pos = ccdPositionList[ccdId]

        ccd.remove("offset")
        ccd.add("offset", pos.centerX)
        ccd.add("offset", pos.centerY)

        ccd.remove("orientation")
        ccd.add("orientation", 0.0) # pitch
        ccd.add("orientation", 0.0) # roll
        ccd.add("orientation", pos.angle * deg) # yaw

    #
    # Save the geometry
    #

    # The standard PAFWriter doesn't print comments.
    # So we do it for ourselves.
    schema = {
        'Raft': [ "0", "", {
            'nCol'  : [ "0", "", None ],
            'nRow'  : [ "1", "", None ],
            'name'  : [ "2", "", None ],
            'serial': [ "3", "", None ],
            'Ccd'   : [ chr(0xff), "", {
                'serial'     : [ "0", "", None ],
                'name'       : [ "1", "", None ],
                'ptype'      : [ "2", "", None ],
                'index'      : [ "3", "", None ],
                'offset'     : [ "4", "offset of CCD center from raft center, (x, y)", None ],
                'nQuarter'   : [ "5", "number of quarter turns applied to CCD when put into raft", None ],
                'orientation': [ "6", "pitch, roll, yaw; degrees", None ],
            }],
        }],
    }
    strList = _policyToStrList([], "Raft", raft, schema["Raft"])

    maxLeftPane = max(len(left) for left, right in strList)

    if not hasattr(output, "write"):
        output = open(output, "w")

    for left, right in strList:
        output.write(left)
        if right:
            output.write(" " * (maxLeftPane - len(left)) + " # " + right)
        output.write("\n")

def _policyToStrList(strList, name, policy, schema, indent = 4, depth = 0):
    """
    Add a policy to two-column string list.
    @param strList: List of double string. e.g.
        [ [ "aaa", "comment to a" ],
          [ "bbb", "comment to b" ],
          ...
        ]
    @param name:   the name of the policy to add
    @param policy: the policy object to add
    @param schema: schema of the policy. It is a tuple:
        [ "priority", "comment", schema ].
        In the triple, "priority", if not None, is the priority, in sorting,
        of the policy among brothers. The name string is simply replaced with
        the priority string before put into sort().
        "comment", if not None, is the comment to the policy. It will
        appear in the right column of the output.
        The last term in the triple, if not None, is the schema dictionary
        for child fields. It is in the form:
            { "child1": [ "priority", "comment", schema ],
              "child2": [ "priority", "comment", schema ],
              ...
            }
    @param indent: Number of spaces for an indent
    @param depth: indent depth, incremented by indent

    @return strList
    """
    if schema and schema[1]:
        comment = schema[1]
    else:
        comment = ""

    if schema and schema[2]:
        childSchemata = schema[2]
    else:
        childSchemata = {}

    strList.append([
        " " * depth + name + ": {", comment
    ])

    for child in sorted(
        policy.names(True),
        key = lambda x: childSchemata[x][0]
            if (x in childSchemata and childSchemata[x][0])
            else x
    ):
        chSch = childSchemata[child] if child in childSchemata else None
        strList = _policyChildToStrList(
            strList, child, policy, chSch, indent, depth + indent
        )

    strList.append([
        " " * depth + "}",
        ""
    ])

    return strList

def _policyChildToStrList(strList, child, policy, schema, indent, depth):
    """
    Add a member of a policy to two-column string list.
    @param strList: List of double string. e.g.
        [ [ "aaa", "comment to a" ],
          [ "bbb", "comment to b" ],
        ]
    @param child:  the name of a member of the policy to add
    @param policy: the policy object whose member to add
    @param schema: schema of the child. It is a tuple:
        [ "priority", "comment", schema ].
        In the triple, "priority", if not None, is the priority, in sorting,
        of the policy among brothers. The name string is simply replaced with
        the priority string before put into sort().
        "comment", if not None, is the comment to the policy. It will
        appear in the right column of the output.
        The last term in the triple, if not None, is the schema dictionary
        for grand-child fields -- valid if the child is a policy. It is in
        the form:
            { "child1": [ "priority", "comment", schema ],
              "child2": [ "priority", "comment", schema ],
              ...
            }
    @param indent: Number of spaces for an indent
    @param depth: indent depth, incremented by indent

    @return strList
    """
    if policy.isPolicy(child):
        for item in policy.getArray(child):
            strList = _policyToStrList(strList, child, item, schema, indent, depth)
        return strList

    if policy.isBool(child):
        format = lambda x: ("true" if x else "false")
    elif policy.isInt(child):
        format = lambda x: "%d" % x
    elif policy.isDouble(child):
        format = lambda x: "%.16e" % x
    elif policy.isString(child):
        format = lambda x: '"' + x + '"'
    else:
        raise ValueError("Policy contains a strange field")

    strList.append([
        " " * depth + child + ": "
            + ' '.join(format(x) for x in policy.getArray(child)),
        schema[1] if (schema and schema[1]) else ""
    ])

    return strList
