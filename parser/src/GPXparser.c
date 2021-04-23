#include "GPXParser.h"
#include "LinkedListAPI.h"

/*
*   File was written by Vrushang Patel (id# 1101823)
*   CIS*2750 Assignment 1 + 2
*/

void deleteGpxData(void* data) {

    if (data == NULL){
        return;
    }
    GPXData* GPXDataContent;
    GPXDataContent = (GPXData*)data;
    free(GPXDataContent);
}
char* gpxDataToString( void* data) {
    if (data == NULL){
        return NULL;
    }

    char* pointer_toString;
    GPXData* GPXData_content;
    int GPXData_size;

    GPXData_content = (GPXData*)data;
    GPXData_size = sizeof(GPXData_content->name) + 10000;
    pointer_toString = (char*)malloc(sizeof(char)*GPXData_size);

    sprintf(pointer_toString, "GPX Name: %s\nGPX Value: %s\n", GPXData_content->name, GPXData_content->value);
    return pointer_toString;
}
int compareGpxData(const void *first, const void *second) {
    if (first == NULL || second == NULL){
		return 0;
	}
    GPXData* tmpName1 = (GPXData *)first;
    GPXData* tmpName2 = (GPXData *)second;

    if (strcmp(tmpName1 ->name, tmpName2 ->name) == 0) {
        if (strcmp(tmpName1 ->value, tmpName2 ->value) == 0) {
            return 0;
        }
    }
    return 1;
}

void deleteWaypoint(void* data) {
	if (data == NULL){
		return;
	}
	Waypoint* tmpName = (Waypoint*)data;

	free(tmpName->name);
    freeList(tmpName -> otherData);
	free(tmpName);
}
char* waypointToString( void* data) {
    if (data == NULL){
		return NULL;
	}

    char* tmpStr;
	int len;
	Waypoint* tmpName = (Waypoint*)data;

	len = strlen(tmpName -> name) + sizeof(tmpName -> latitude) + sizeof(tmpName -> longitude) + 10000;
	tmpStr = (char*)malloc(sizeof(char)*len);

    char*tmp = toString(tmpName->otherData);
    if (strcmp(tmp, "") == 0){
        sprintf(tmpStr, "      namespace ->        %s\n      latitude->          %f\n      longitude->         %f\n", tmpName -> name, tmpName -> latitude, tmpName -> longitude);
    } else {
        sprintf(tmpStr, "      namespace ->        %s\n      latitude->          %f\n      longitude->         %f\n        otherDate->         %s\n", tmpName -> name, tmpName -> latitude, tmpName -> longitude, tmp);
    }

    free(tmp);
	return tmpStr;
}
int compareWaypoints(const void *first, const void *second) {
    if (first == NULL || second == NULL){
		return 0;
	}

	Waypoint* tmpName1 = (Waypoint*)first;
	Waypoint* tmpName2 = (Waypoint*)second;

    if (strcmp((char*)tmpName1 ->name, (char*)tmpName2 ->name) == 0) {
        if (tmpName1 -> latitude == tmpName2 -> latitude) {
            if (tmpName1 -> longitude ==  tmpName2 -> longitude)
            {
                return 0;
            }
        }
    }

    return 1;
}

void deleteRoute(void* data) {
	if (data == NULL){
		return;
	}
	Route* tmpName = (Route*)data;

	free(tmpName->name);
    freeList(tmpName -> waypoints);
    freeList(tmpName -> otherData);
	free(tmpName);
}
char* routeToString(void* data) {
	if (data == NULL){
		return NULL;
	}
    char* tmpStr;
	int len;
	Route* tmpName = (Route*)data;

	len = strlen(tmpName->name) +10000;
	tmpStr = (char*)malloc(sizeof(char)*len);

    char *tmp = toString(tmpName ->waypoints);
    char*tmp2 = toString(tmpName ->otherData);
	sprintf(tmpStr, "  Route Name:             %s\n%s\n%s\n", tmpName->name, tmp, tmp2);
    free(tmp);
    free(tmp2);

	return tmpStr;
}
int compareRoutes(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}
	Route* tmpName1 = (Route*)first;
	Route* tmpName2 = (Route*)second;

    if (strcmp((char*)tmpName1 ->name, (char*)tmpName2 ->name) == 0) {
        if (compareWaypoints(tmpName1 ->waypoints, tmpName2 ->waypoints) == 0) {
            return 0;
        }
    }

    return 1;
}

void deleteTrackSegment(void* data) {
	if (data == NULL){
		return;
	}

	TrackSegment* tmpName = (TrackSegment*)data;

	freeList(tmpName->waypoints);
	free(tmpName);
}
char* trackSegmentToString(void* data) {
    if (data == NULL){
		return NULL;
	}
    char* tmpStr;
	int len;
	TrackSegment* tmpName = (TrackSegment*)data;

	len = 10000;
	tmpStr = (char *)malloc(sizeof(char)* len);

    char *tmp = toString(tmpName -> waypoints);
    sprintf(tmpStr, "    Track Segments:\n%s\n", tmp);
    free(tmp);

	return tmpStr;
}
int compareTrackSegments(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}
    TrackSegment* tmpName1;
    tmpName1 = (TrackSegment*)first;
    Node* tmp1 = tmpName1 ->waypoints ->head;

	TrackSegment* tmpName2;
	tmpName2 = (TrackSegment*)second;
    Node* tmp2 = tmpName2 -> waypoints -> head;

	while(tmp1 != NULL || tmp2 != NULL){
		if (compareWaypoints(tmp1 ->data, tmp2->data) == 0){
		}else{
			return 1;
		}
	}

    return 0;
}

void deleteTrack(void* data) {
    if (data == NULL){
		return;
	}
	Track* tmpName = (Track*)data;

    free(tmpName -> name);
	freeList(tmpName -> segments);
    freeList(tmpName -> otherData);
	free(tmpName);
}
char* trackToString(void* data) {
    if (data == NULL){
		return NULL;
	}
    char* tmpStr;
	int len;
	Track* tmpName = (Track*)data;

	len = strlen(tmpName -> name)+  10000;
	tmpStr = (char*)malloc(sizeof(char)*len);

    char *tmp = toString(tmpName -> segments);
    char *tmp2 = toString(tmpName -> otherData);
    sprintf(tmpStr, "  Track Name:              %s\n%s\n%s\n", tmpName -> name, tmp, tmp2);
    free(tmp);
    free(tmp2);

	return tmpStr;
}
int compareTracks(const void *first, const void *second) {
	if (first == NULL || second == NULL){
		return 0;
	}
    Track* tmpName1;
	tmpName1 = (Track*)first;

	Track* tmpName2;
	tmpName2 = (Track*)second;

    if (strcmp((char*)tmpName1 ->name, (char*)tmpName2 ->name) == 0) {
        if (compareTrackSegments(tmpName1 ->segments, tmpName2 ->segments) == 0) {
            return 0;
        }
    }

    return 1;
}

void deleteGPXdoc(GPXdoc *doc) {
    if ( doc == NULL) {
        return;
    }
    free(doc -> creator);
    freeList(doc ->waypoints);
    freeList(doc ->routes);
    freeList(doc->tracks);
    free(doc);
}

GPXData *writeGPXData(xmlNode *node) {
    if (node == NULL) {
        return NULL;
    }

    GPXData *gpxdata_creator = malloc(sizeof(GPXData) +100*sizeof(char));
    xmlNode *temp;
    xmlNode *temp2;

    temp = node;
    temp2 = temp -> children;

    if (temp2 != NULL) {
        if (temp2 -> content != NULL) {
            strcpy(gpxdata_creator -> name, (char*)(temp->name) );
            strcpy(gpxdata_creator -> value,(char*)(temp2->content) );
            return (void *)gpxdata_creator;
        }
    }

    free(gpxdata_creator);
    return NULL;
}

Waypoint *writeWaypoint (xmlNode * node) {
    if (node == NULL) {
        return NULL;
    }

    xmlAttr *attr;
    xmlNode *value;
    xmlNode *temp = NULL;
    xmlNode *temp2 = NULL;
    Waypoint *waypoint_creator = (Waypoint *)malloc(sizeof(Waypoint));
    List * listGPX = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    waypoint_creator -> otherData = listGPX;

    for (attr = node->properties; attr != NULL; attr = attr->next) {
        value = attr->children;
        if (strcmp("lat", (char *)(attr->name)) == 0) {
            waypoint_creator -> latitude = strtod((char *)(value->content), NULL);
        }
        if (strcmp("lon", (char *)(attr->name)) == 0) {
            waypoint_creator -> longitude = strtod((char *)(value->content), NULL);
        }
    }
    waypoint_creator -> name = NULL;
    for (temp = node ->children; temp != NULL; temp = temp -> next) {
        if  ( (strcmp("name", (char *)(temp->name)) == 0) ) {
            temp2 = temp -> children;
            if (temp2 != NULL) {
                char* cont =  (char *)(temp2 ->content);
                if (temp2 -> content != NULL) {
                    int len =  strlen(cont);
                    waypoint_creator -> name = (char *)malloc(len + 1);

                    strcpy(waypoint_creator -> name, (char *)(temp2 ->content));
                }
            }
        } else if ((strcmp("text", (char *)(temp->name)) != 0) ) {
            insertBack( (waypoint_creator->otherData), writeGPXData(temp));
        }
    }
    if (waypoint_creator -> name == NULL)
    {
        int len =  strlen("");
        waypoint_creator -> name = (char *)malloc(len + 1);

        strcpy(waypoint_creator -> name, "");
    }

    return (void *)waypoint_creator;
}

Route *writeRoute (xmlNode * a_node) {
    if (a_node == NULL) {
        return NULL;
    }
    xmlNode *temp = NULL;
    xmlNode *node = NULL;
    Route *route_creator = (Route *)malloc(sizeof(Route));
    List *listWaypoint = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    route_creator -> waypoints = listWaypoint;

    List *listGPXData = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    route_creator -> otherData = listGPXData;

    route_creator -> name = NULL;
    for (temp = a_node ->children; temp != NULL; temp = temp -> next) {
        if (strcmp("name", (char *)temp -> name) == 0 ) {
            node = temp -> children;
            if (node != NULL) {
                char* cont =  (char *)(node ->content);
                if (node -> content != NULL) {
                    int len =  strlen(cont);
                    route_creator -> name = (char *)malloc(len + 1);

                    strcpy(route_creator -> name, (char *)(node ->content));
                }
            }
        } else if ((strcmp("rtept", (char *)temp -> name) == 0) ) {
            insertBack(route_creator -> waypoints, writeWaypoint( temp));
        } else if ((strcmp("text", (char *)temp -> name) != 0) ) {
            insertBack( (route_creator -> otherData), writeGPXData(temp));
        }
    }
    if (route_creator -> name == NULL) {
        int len =  strlen("");
        route_creator -> name = (char *)malloc(len + 1);

        strcpy(route_creator -> name, "");
    }
    return (void *)route_creator;
}

TrackSegment * writeTrackSegment(xmlNode *a_node) {
    if (a_node == NULL) {
        return NULL;
    }
    xmlNode *temp = NULL;
    TrackSegment *trackSegment_creator = (TrackSegment *)malloc(sizeof(TrackSegment));
    List *listWaypoint = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    trackSegment_creator -> waypoints = listWaypoint;

    for (temp = a_node ->children; temp != NULL; temp = temp -> next) {
        if  (strcmp("trkpt", (char *)temp -> name) == 0) {
            insertBack(trackSegment_creator -> waypoints, writeWaypoint( temp));
        }
    }
    return (void *)trackSegment_creator;
}

Track *writeTrack(xmlNode * a_node) {
    if (a_node == NULL) {
        return NULL;
    }
    xmlNode *temp = NULL;
    xmlNode *node = NULL;
    Track *track_creator = (Track *)malloc(sizeof(Track));
    List *listWTrackSegment = initializeList(&trackSegmentToString, &deleteTrackSegment, &compareTrackSegments);
    track_creator -> segments = listWTrackSegment;

    List *listGPX = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    track_creator -> otherData = listGPX;

    for (temp = a_node ->children; temp != NULL; temp = temp -> next) {
        if  ( (strcmp("name", (char *)(temp->name)) == 0) ) {
            node = temp -> children;
            if (node != NULL) {
                char* cont =  (char *)(node ->content);
                if (node -> content != NULL) {
                    int len =  strlen(cont);
                    track_creator -> name = (char *)malloc(len + 1);

                    strcpy(track_creator -> name, (char *)(node ->content));
                }
            }
        } else if  ( (strcmp("trkseg", (char *)(temp->name)) == 0) ) {
            insertBack(track_creator -> segments, writeTrackSegment(temp));
        } else if  ( (strcmp("text", (char *)(temp->name)) != 0) ) {
            insertBack( (track_creator->otherData), writeGPXData(temp));
        }
    }
    if (track_creator -> name == NULL) {
        int len =  strlen("");
        track_creator -> name = (char *)malloc(len + 1);

        strcpy(track_creator -> name, "");
    }
    return (void *)track_creator;
}

static void writeGPX(GPXdoc *doc_content, xmlNode * a_node) {
    xmlNode *node = a_node;
    xmlNs *namesp = NULL;

    for (; node != NULL; node = node->next) {
        xmlAttr *attr;
        // xmlNode *value;
        if (node->type == XML_ELEMENT_NODE) {
            if ((strcmp("wpt", (char *)(node->name)) == 0 )) {
                insertBack(doc_content -> waypoints, writeWaypoint(node));
            } else if (strcmp("rte", (char *)(node->name)) == 0) {
                insertBack(doc_content -> routes, writeRoute(node));
            } else if (strcmp("trk", (char *)(node->name)) == 0) {
                insertBack(doc_content -> tracks, writeTrack(node));
            }
        }

        for (attr = node->properties; attr != NULL; attr = attr->next) {
            xmlNode *value = attr->children;
            if (value != NULL) {
                namesp = node -> ns;
                strcpy(doc_content -> namespace, (char *)namesp -> href);
                char *cont = (char *)(value->content);
                if (strcmp("version", (char *)(attr->name)) == 0) {
                    doc_content->version = strtod((char *)(value->content), NULL);
                }
                if (strcmp("creator", (char *)(attr->name)) == 0) {
                    int len =  strlen(cont);
                    doc_content -> creator = (char *)malloc(len + 1);
                    strcpy(doc_content -> creator, (char *)(value->content));
                }
            }
        }
        writeGPX(doc_content, node->children);
    }
}

char * GPXdocToString (GPXdoc *doc_content) {
    if (doc_content == NULL) {
        return NULL;
    }

    char *temp_doc_content;
    int length_doc = 0;

    length_doc = sizeof(doc_content->version) + strlen(doc_content->creator) +sizeof(doc_content ->waypoints) + 100;
    temp_doc_content = (char *)malloc(sizeof(char) * length_doc);
    sprintf(temp_doc_content, "version -> %f\ncreator -> %s\nnamespace -> %s\n", doc_content -> version, doc_content -> creator, doc_content -> namespace);

    char *tmp1 = toString(doc_content->waypoints);
    char *tmp2 = toString(doc_content->routes);
    char *tmp3 = toString(doc_content->tracks);

    printf("<---======DOC -> WAYPOINTS======--->\n");
    printf(tmp1);
    printf("<---======~~~~~~~~~~~~~~~~======--->\n");
    printf("<---======~~DOC -> ROUTES~=====--->\n");
    printf(tmp2);
    printf("<---======~~~~~~~~~~~~~~~~======--->\n");
    printf("<---======~~DOC -> TRACK~~======--->\n");
    printf(tmp3);
    printf("<---======~~~~~~~~~~~~~~~~======--->\n");

    free(tmp1);
    free(tmp2);
    free(tmp3);
    return temp_doc_content;
}

GPXdoc *createGPXdoc(char *filename) {
    if (filename == NULL) {
        return NULL;
    }

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    LIBXML_TEST_VERSION
    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL) {
        return NULL;
    }

    GPXdoc *doc_content = malloc(sizeof(GPXdoc));

    List *listWaypoint = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    List *listRoute = initializeList(&routeToString, &deleteRoute, &compareRoutes);
    List *listTrack = initializeList(&trackToString, &deleteTrack, &compareTracks);

    doc_content -> waypoints = listWaypoint;
    doc_content -> routes = listRoute;
    doc_content -> tracks = listTrack;

    root_element = xmlDocGetRootElement(doc);

    writeGPX(doc_content, root_element);

    xmlFreeDoc(doc);
    return doc_content;
}

int getNumWaypoints(const GPXdoc* doc) {
    int i = 0;
    if (doc == NULL) {
        return 0;
    }
    if (doc -> waypoints == NULL) {
        return 0;
    }

    Node* iter = (doc ->waypoints)->head;
    while (iter !=NULL) {
        i++;
        iter = iter -> next;
    }

    return i;
}

int getNumRoutes(const GPXdoc* doc) {
    int i = 0;
    if (doc == NULL) {
        return 0;
    }
    if (doc -> tracks == NULL) {
        return 0;
    }

    Node* iter = (doc ->routes)->head;

    while (iter !=NULL) {
        i++;
        iter = iter -> next;
    }

    return i;
}

int getNumTracks(const GPXdoc* doc) {
    int i = 0;
    if (doc == NULL) {
        return 0;
    }
    if (doc -> tracks == NULL) {
        return 0;
    }

    Node* iter = (doc ->tracks)->head;
    while (iter !=NULL) {
        i++;
        iter = iter -> next;
    }

    return i;
}

int getNumSegments(const GPXdoc* doc) {
    if (doc == NULL) {
        return 0;
    }
    if (doc -> tracks == NULL) {
        return 0;
    }
    int i = 0;
    Node* iter = (doc -> tracks) -> head;
    while (iter !=NULL) {
        Track * trk_ptr = (Track *) iter -> data;
        if (trk_ptr -> segments  != NULL) {
            if (trk_ptr -> segments != NULL) {
                Node *iter2 = trk_ptr -> segments -> head;
                while (iter2 != NULL) {
                    iter2 = iter2 -> next;
                    i++;
                }
            }
        }
        iter = iter -> next;
    }

    return i;
}


int waypointOther(Node *waypointList) {
    int i = 0;
    while (waypointList != NULL) {
        Waypoint *iter = (Waypoint *)waypointList -> data;
        if (strcmp(iter -> name, "") != 0) {
            i++;
        }
        if (iter -> otherData -> head != NULL) {
            Node *otherDataNode = iter -> otherData -> head;
            GPXData *g = (GPXData *)otherDataNode -> data;
            if (iter -> name == NULL) {
            } else {
                while (otherDataNode != NULL) {
                    if (strcmp(g -> name, "") != 0) {
                        i++;
                    }
                    otherDataNode = otherDataNode -> next;
                    if (otherDataNode != NULL) {
                        g = otherDataNode -> data;
                    }
                }
            }
        }

        waypointList = waypointList -> next;
    }
    return i;
}
int routeOther(Node *routeList) {
    int i = 0;
    while (routeList != NULL) {
        Route *iter = (Route *)routeList -> data;
        if (strcmp(iter -> name, "name")) {
            i++;
        }
        if (iter -> otherData -> head != NULL) {
            Node *otherDataNode = iter -> otherData -> head;
            GPXData *g = (GPXData *)otherDataNode -> data;
            if (iter -> name == NULL) {
            } else {
                while (otherDataNode != NULL) {
                    if (strcmp(g -> name, "") != 0) {
                        i++;
                    }
                    otherDataNode = otherDataNode -> next;
                    if (otherDataNode != NULL) {
                        g = otherDataNode -> data;
                    }
                }
            }
        }
        if (iter -> waypoints -> head != NULL) {
            Node *waypointNode = iter -> waypoints -> head;
            i += waypointOther(waypointNode);
        }
        routeList = routeList -> next;
    }
    return i;
}
int TrackOther(Node *trackList) {
    int i = 0;
    while (trackList != NULL) {
        Track *iter = (Track *)trackList -> data;
        if (strcmp(iter -> name, "name")) {
            i++;
        }
        if (iter -> otherData -> head != NULL) {
            Node *otherDataNode = iter -> otherData -> head;
            GPXData *g = (GPXData *)otherDataNode -> data;
            if (iter -> name == NULL) {
            } else {
                while (otherDataNode != NULL) {
                    if (strcmp(g -> name, "") != 0) {
                        i++;
                    }
                    otherDataNode = otherDataNode -> next;
                    if (otherDataNode != NULL) {
                        g = otherDataNode -> data;
                    }
                }
            }
        }

        if (iter -> segments -> head != NULL) {
            Node *segmentNode = iter -> segments -> head;
            TrackSegment *z = (TrackSegment *)segmentNode -> data;
            while (segmentNode != NULL) {
                if (z -> waypoints -> head != NULL) {
                    Node *waypointNode = z -> waypoints -> head;
                    i += waypointOther(waypointNode);

                    segmentNode = segmentNode -> next;
                    if (segmentNode != NULL) {
                        z = segmentNode -> data;
                    }
                }
            }
        }
        trackList = trackList -> next;
    }
    return i;
}

int getNumGPXData (const GPXdoc * doc) {
    if (doc == NULL) {
        return 0;
    }
    if (doc -> waypoints == NULL) {
        return 0;
    }
    if (doc -> routes == NULL) {
        return 0;
    }
    if (doc -> tracks == NULL) {
        return 0;
    }
    List * waypointOD = doc -> waypoints;
    List * routeOD = doc -> routes;
    List * trackOD = doc -> tracks;

    Node * waypointHeadOD = waypointOD -> head;
    Node * routeHeadOD = routeOD -> head;
    Node * trackHeadOD = trackOD -> head;

    return waypointOther(waypointHeadOD) + routeOther(routeHeadOD) + TrackOther(trackHeadOD);
}

bool validGPXData(const GPXdoc *doc) {

    if (doc == NULL) {
        return false;
    }

    List *list_track = doc->tracks;
    Node *trk_iter = list_track->head;
    while (trk_iter != NULL) {
        Track *trk_ptr = (Track *)trk_iter->data;
        Node *oth_iter = trk_ptr->otherData->head;
        while (oth_iter != NULL) {
            GPXData *gpx_ptr = (GPXData *)oth_iter->data;
            if (gpx_ptr -> name == NULL) {
                return false;
            }
            oth_iter = oth_iter -> next;
        }

        Node *seg_iter = trk_ptr -> segments -> head;
        while (seg_iter != NULL) {
            TrackSegment *seg_ptr = (TrackSegment *)seg_iter->data;
            Node *wpt_iter = seg_ptr -> waypoints -> head;
            while (wpt_iter != NULL) {
                Waypoint *wpt_ptr = (Waypoint *)wpt_iter -> data;
                if (wpt_ptr -> name == NULL) {
                    return false;
                }
                Node *oth_iter2 = wpt_ptr -> otherData -> head;
                while (oth_iter2 != NULL) {
                    GPXData *gpx_ptr2 = (GPXData *)oth_iter2->data;
                    if (gpx_ptr2 -> name == NULL) {
                        return false;
                    }
                    oth_iter2 = oth_iter2 -> next;
                }
                wpt_iter = wpt_iter -> next;
            }
            seg_iter = seg_iter -> next;
        }
        trk_iter = trk_iter -> next;
    }


    List *list_route = doc->routes;
    Node *rte_iter = list_route->head;
    while (rte_iter != NULL) {
        Route *rte_ptr = (Route *)rte_iter -> data;
        if (rte_ptr->name == NULL) {
            return false;
        }

        Node *oth_iter = rte_ptr -> otherData -> head;
        while (oth_iter != NULL) {
            GPXData *gpx_ptr = (GPXData *)oth_iter -> data;
            if (gpx_ptr -> name == NULL) {
                return false;
            }
            oth_iter = oth_iter -> next;
        }

        Node *wpt_iter = rte_ptr -> waypoints -> head;
        while (wpt_iter != NULL) {
            Waypoint *wpt_ptr = (Waypoint *)wpt_iter -> data;
            if (wpt_ptr -> name == NULL) {
                return false;
            }
            Node *oth_iter2 = wpt_ptr -> otherData -> head;
            while (oth_iter2 != NULL) {
                GPXData *gpx_ptr2 = (GPXData *)oth_iter2->data;
                if (gpx_ptr2 -> name == NULL) {
                    return false;
                }
                oth_iter2 = oth_iter2 -> next;
            }
            wpt_iter = wpt_iter -> next;
        }
        rte_iter = rte_iter -> next;
    }


    List *list_waypoint = doc->waypoints;
    Node *wpt_iter = list_waypoint->head;
    while (wpt_iter != NULL) {
        Waypoint *wpt_ptr = (Waypoint *)wpt_iter -> data;
        if (wpt_ptr->name == NULL) {
            return false;
        }

        Node *oth_iter = wpt_ptr -> otherData -> head;
        while (oth_iter != NULL) {
            GPXData *gpx_ptr = (GPXData *)oth_iter -> data;
            if (gpx_ptr -> name == NULL) {
                return false;
            }
            oth_iter = oth_iter -> next;
        }
        wpt_iter = wpt_iter -> next;
    }

    return true;
}


Waypoint* getWaypoint(const GPXdoc* doc, char* name) {
    if (doc == NULL) {
        return NULL;
    }
    if (doc -> waypoints == NULL) {
        return NULL;
    }
    if (name == NULL) {
        return NULL;
    }

    List * waypointOD = doc -> waypoints;
    Node * waypointHeadOD = waypointOD -> head;
    while (waypointHeadOD != NULL) {
        Waypoint *iter = (Waypoint *) waypointHeadOD ->data;
        if (strcmp(iter -> name, name) == 0) {
            return iter;
        }
        waypointHeadOD = waypointHeadOD -> next;
    }

    return NULL;
}
Track* getTrack(const GPXdoc* doc, char* name) {
    if (doc == NULL) {
        return NULL;
    }
    if (doc -> tracks == NULL) {
        return NULL;
    }
    if (name == NULL) {
        return NULL;
    }

    List * trackOD = doc -> tracks;
    Node * trackHeadOD = trackOD -> head;
    while (trackHeadOD != NULL) {
        Track *iter = (Track *) trackHeadOD -> data;
        if (strcmp(iter -> name, name) == 0) {
            return iter;
        }
        trackHeadOD = trackHeadOD -> next;
    }
    return NULL;
}
Route* getRoute(const GPXdoc* doc, char* name) {
    if (doc == NULL) {
        return NULL;
    }
    if (doc -> routes == NULL) {
        return NULL;
    }
    if (name == NULL) {
        return NULL;
    }

    List * routeOD = doc -> routes;
    Node * routeHeadOD = routeOD -> head;
    while (routeHeadOD != NULL) {
        Route * iter = (Route *) routeHeadOD -> data;
        if (strcmp(iter -> name, name) == 0) {
            return iter;
        }
        routeHeadOD = routeHeadOD -> next;
    }
    return NULL;
}


bool validWaypoint(const GPXdoc *doc) {
    if (doc == NULL) {
        return false;
    }
    if (doc -> waypoints == NULL) {
        return false;
    }

    Node* iter = (doc -> waypoints)->head;
    while (iter != NULL) {
        if (iter -> data == NULL) {
            return false;
        }
        iter = iter -> next;
    }

    return true;
}
bool validRoute(const GPXdoc *doc) {
    if (doc == NULL) {
        return false;
    }
    if (doc -> tracks == NULL) {
        return false;
    }

    Node* iter = (doc ->routes)->head;

    while (iter != NULL) {
        if (iter -> data == NULL) {
            return false;
        }
        iter = iter -> next;
    }

    return true;
}
bool validTrack(const GPXdoc *doc) {
    if (doc == NULL) {
        return 0;
    }
    if (doc -> tracks == NULL) {
        return 0;
    }

    Node* iter = (doc ->tracks)->head;

    while (iter !=NULL) {
        if (iter -> data == NULL) {
            return false;
        }
        iter = iter -> next;
    }

    return true;
}
bool validSegment(const GPXdoc *doc) {
    if (doc == NULL) {
        return 0;
    }
    if (doc -> tracks == NULL) {
        return 0;
    }

    Node* iter = (doc -> tracks) -> head;
    while (iter !=NULL) {
        Track * trk_ptr = (Track *) iter -> data;
        if (trk_ptr -> segments  != NULL) {
            Node *iter2 = trk_ptr -> segments -> head;
            while (iter2 != NULL) {
                if (iter2 -> data == NULL) {
                    return false;
                }
                iter2 = iter2 -> next;
            }
        }
        iter = iter -> next;
    }

    return true;
}

GPXdoc *createValidGPXdoc(char *fileName, char *gpxSchemaFile) {
    if (fileName == NULL) {
        return false;
    }
    if (gpxSchemaFile == NULL) {
        return false;
    }

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    LIBXML_TEST_VERSION


    xmlSchemaParserCtxtPtr ctxt = xmlSchemaNewParserCtxt(gpxSchemaFile);
    xmlSchemaPtr schema = xmlSchemaParse(ctxt);

    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
    xmlSchemaFreeParserCtxt(ctxt);

    doc = xmlReadFile(fileName, NULL, 0);
    if (doc == NULL) {
        xmlSchemaFree(schema);
        return NULL;
    } else {

        xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
        int ret = xmlSchemaValidateDoc(ctxt, doc);

        if (ret == 0) {
            root_element = xmlDocGetRootElement(doc);

            GPXdoc *doc_content = malloc(sizeof(GPXdoc));

            List *listWaypoint = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
            List *listRoute = initializeList(&routeToString, &deleteRoute, &compareRoutes);
            List *listTrack = initializeList(&trackToString, &deleteTrack, &compareTracks);

            doc_content->waypoints = listWaypoint;
            doc_content->routes = listRoute;
            doc_content->tracks = listTrack;


            writeGPX(doc_content, root_element);

            xmlSchemaFreeValidCtxt(ctxt);
            xmlSchemaFree(schema);
            xmlSchemaCleanupTypes();

            xmlCleanupParser();
            xmlMemoryDump();
            xmlFreeDoc(doc);

            return doc_content;
        } else {
            xmlSchemaFreeValidCtxt(ctxt);
            xmlSchemaFree(schema);
            xmlSchemaCleanupTypes();
            xmlCleanupParser();
            xmlMemoryDump();
            xmlFreeDoc(doc);
            return NULL;
        }
    }
}

bool writeGPXdoc(GPXdoc *doc_content, char *fileName) {
    if (doc_content == NULL) {
        return false;
    }
    if (fileName == NULL) {
        return false;
    }

    xmlDoc *doc = NULL;
    xmlNodePtr root_node = NULL, node = NULL, node1 = NULL, node2 = NULL;
    char s[50];

    LIBXML_TEST_VERSION;
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "gpx");
    if (root_node == NULL) {
        return false;
    }

    xmlDocSetRootElement(doc, root_node);
    xmlNewProp(root_node, BAD_CAST "creator", BAD_CAST doc_content->creator);
    sprintf(s, "%.1f", doc_content->version);
    xmlNewProp(root_node, BAD_CAST "version", BAD_CAST s);
    xmlSetNs(root_node, xmlNewNs(root_node, BAD_CAST doc_content->namespace, NULL));

    Node *wpt_iter = (doc_content->waypoints)->head;
    while (wpt_iter != NULL) {
        Waypoint *wpt_ptr = (Waypoint *)wpt_iter->data;

        node = xmlNewChild(root_node, NULL, BAD_CAST "wpt", NULL);
        xmlNewChild(node, NULL, BAD_CAST "name", BAD_CAST wpt_ptr->name);
        sprintf(s, "%.5f", wpt_ptr->latitude);
        xmlNewProp(node, BAD_CAST "lat", BAD_CAST s);
        sprintf(s, "%.5f", wpt_ptr->longitude);
        xmlNewProp(node, BAD_CAST "lon", BAD_CAST s);

        Node *oth_iter = wpt_ptr->otherData->head;
        while (oth_iter != NULL) {
            GPXData *g = (GPXData *)oth_iter->data;
            xmlNewChild(node, NULL, BAD_CAST g->name, BAD_CAST g->value);
            oth_iter = oth_iter -> next;
        }
        wpt_iter = wpt_iter->next;
    }

    Node *rte_iter = (doc_content->routes)->head;
    while (rte_iter != NULL) {
        Route *rte_ptr = (Route *)rte_iter->data;

        node = xmlNewChild(root_node, NULL, BAD_CAST "rte", NULL);
        xmlNewChild(node, NULL, BAD_CAST "name", BAD_CAST rte_ptr->name);

        Node *oth_iter = rte_ptr->otherData->head;
        while (oth_iter != NULL) {
            GPXData *g = (GPXData *)oth_iter->data;
            xmlNewChild(node, NULL, BAD_CAST g->name, BAD_CAST g->value);
            oth_iter = oth_iter -> next;
        }

        Node *wpt_iter = rte_ptr->waypoints->head;
        while (wpt_iter != NULL) {
            Waypoint *wpt_ptr = (Waypoint *)wpt_iter->data;

            node1 = xmlNewChild(node, NULL, BAD_CAST "rtept", NULL);
            sprintf(s, "%.6f", wpt_ptr->latitude);
            xmlNewProp(node1, BAD_CAST "lat", BAD_CAST s);
            sprintf(s, "%.6f", wpt_ptr->longitude);
            xmlNewProp(node1, BAD_CAST "lon", BAD_CAST s);

            if (strcmp("", wpt_ptr->name) != 0) {
                xmlNewChild(node1, NULL, BAD_CAST "name", BAD_CAST wpt_ptr->name);
            }

            Node *oth_iter2 = wpt_ptr->otherData->head;
            while (oth_iter2 != NULL) {
                GPXData *g = (GPXData *)oth_iter2 ->data;
                xmlNewChild(node1, NULL, BAD_CAST g->name, BAD_CAST g->value);
                oth_iter2  = oth_iter2 ->next;
            }
            wpt_iter = wpt_iter->next;
        }
        rte_iter = rte_iter->next;
    }

    Node *trk_iter = (doc_content->tracks)->head;
    while (trk_iter != NULL) {
        Track *trk_ptr = (Track *)trk_iter->data;

        node = xmlNewChild(root_node, NULL, BAD_CAST "trk", NULL);
        if (strcmp("", trk_ptr->name) != 0) {
            xmlNewChild(node, NULL, BAD_CAST "name", BAD_CAST trk_ptr->name);
        }

        Node *oth_iter = trk_ptr->otherData->head;
        while (oth_iter != NULL) {
            GPXData *g = (GPXData *)oth_iter->data;
            xmlNewChild(node, NULL, BAD_CAST g->name, BAD_CAST g->value);
            oth_iter = oth_iter->next;
        }

        Node *seg_iter = trk_ptr->segments->head;
        while (seg_iter != NULL) {
            TrackSegment *seg_ptr = (TrackSegment *)seg_iter->data;

            node1 = xmlNewChild(node, NULL, BAD_CAST "trkseg", NULL);
            Node *wpt_iter = seg_ptr -> waypoints -> head;
            while(wpt_iter != NULL) {
                Waypoint *wpt_ptr = wpt_iter -> data;

                node2 = xmlNewChild(node1, NULL, BAD_CAST "trkpt", NULL);
                sprintf(s, "%.6f", wpt_ptr->latitude);
                xmlNewProp(node2, BAD_CAST "lat", BAD_CAST s);
                sprintf(s, "%.6f", wpt_ptr->longitude);
                xmlNewProp(node2, BAD_CAST "lon", BAD_CAST s);
                if (strcmp("", wpt_ptr->name) != 0) {
                    xmlNewChild(node2, NULL, BAD_CAST "name", BAD_CAST wpt_ptr->name);
                }
                Node *oth_iter2 = wpt_ptr->otherData->head;
                while (oth_iter2 != NULL) {
                    GPXData *g = (GPXData *)oth_iter2->data;
                    xmlNewChild(node2, NULL, BAD_CAST g->name, BAD_CAST g->value);
                    oth_iter2 = oth_iter2->next;
                }
                wpt_iter = wpt_iter -> next;
            }
            seg_iter = seg_iter -> next;
        }
        trk_iter = trk_iter->next;
    }

    if (xmlSaveFormatFileEnc(fileName, doc, "UTF-8", 1) < 0) {
        return false;
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    xmlMemoryDump();

    return true;
}

bool validateGPXDoc(GPXdoc *doc, char *gpxSchemaFile) {

    xmlLineNumbersDefault(1);
    xmlSchemaParserCtxtPtr ctxt = xmlSchemaNewParserCtxt(gpxSchemaFile);
    xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
    xmlSchemaPtr schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    if (doc == NULL) {
        xmlSchemaFree(schema);
        return false;
    } else {
        xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf, (xmlSchemaValidityWarningFunc)fprintf, stderr);
        xmlSchemaFreeValidCtxt(ctxt);
    }

    if ((validWaypoint(doc) == false) || (validRoute(doc) == false) || (validTrack(doc) == false) || (validGPXData(doc) == false) || (validSegment(doc) == false)) {
        xmlSchemaFree(schema);
        return false;
    }

    xmlSchemaFree(schema);
    return true;
}

float round10(float len) {

    int a = (len / 10);
    a = a * 10;
    int b = a + 10;

    int c = (a + b) / 2;

    if (len >= c) {
        return b;
    } else {
        return a;
    }
}

float dist(float lat1, float lon1, float lat2, float lon2) {

    float TO_RAD = M_PI / 180;
    float dx, dy, dz;
    lon1 -= lon2;
    lon1 *= TO_RAD, lat1 *= TO_RAD, lat2 *= TO_RAD;

    dz = sin(lat1) - sin(lat2);
    dx = cos(lon1) * cos(lat1) - cos(lat2);
    dy = sin(lon1) * cos(lat1);
    return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * 6371;
}

float getRouteLen(const Route *rt) {

    if (rt == NULL) {
        return 0;
    }

    float i = 0;
    Node *wpt_iter = rt->waypoints->head;

    while (wpt_iter != NULL) {
        Waypoint *wpt_pnt = (Waypoint *)wpt_iter->data;
        wpt_iter = wpt_iter->next;
        if (wpt_iter != NULL) {
            Waypoint *wpt_pnt2 = (Waypoint *)wpt_iter->data;
            i += dist(wpt_pnt->latitude, wpt_pnt->longitude, wpt_pnt2->latitude, wpt_pnt2->longitude);
        }
    }

    i *= 1000;
    return i;
}

float getTrackLen(const Track *tr) {

    if (tr == NULL) {
        return 0;
    }

    float i = 0;
    Node *trk_iter = tr->segments->head;

    while (trk_iter != NULL) {
        TrackSegment *ts = (TrackSegment *)trk_iter->data;

        Node *wpt_iter = ts->waypoints->head;
        while (wpt_iter != NULL) {
            Waypoint *wpt_pnt = (Waypoint *)wpt_iter->data;
            wpt_iter = wpt_iter->next;
            if (wpt_iter != NULL) {
                Waypoint *wpt_pnt2 = (Waypoint *)wpt_iter->data;
                i += dist(wpt_pnt->latitude, wpt_pnt->longitude, wpt_pnt2->latitude, wpt_pnt2->longitude);
            }
        }

        trk_iter = trk_iter->next;
    }

    i *= 1000;
    return i;
}

int numRoutesWithLength(const GPXdoc *doc, float len, float delta) {
    if (doc == NULL) {
        return 0;
    }
    if (len < 0) {
        return 0;
    }
    if (delta < 0) {
        return 0;
    }

    int i = 0;

    Node *iter = doc->routes->head;
    while (iter != NULL) {
        Route *content_route = (Route *)iter->data;
        float compareVal = getRouteLen(content_route);
        if (compareVal >= len - delta && compareVal <= len + delta) {
            i++;
        }
        iter = iter->next;
    }
    return i;
}

int numTracksWithLength(const GPXdoc *doc, float len, float delta) {

    if (doc == NULL) {
        return 0;
    }
    if (0 > len) {
        return 0;
    }
    if (delta < 0) {
        return 0;
    }

    int i = 0;

    Node *trk_iter = doc->tracks->head;
    while (trk_iter != NULL) {
        Track *node = (Track *)trk_iter->data;
        float compareVal = getTrackLen(node);
        if (compareVal >= len - delta && compareVal <= len + delta) {
            i++;
        }
        trk_iter = trk_iter->next;
    }
    return i;
}

bool isLoopRoute(const Route *route, float delta) {

    if (route == NULL) {
        return false;
    }
    if (delta < 0) {
        return false;
    }
    int wpt_count = 0;
    float lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;

    Node *iter = route->waypoints->head;

    while (iter != NULL){

        Waypoint *node = (Waypoint *)iter->data;

        if (wpt_count == 0) {
            lon1 = node->longitude;
            lat1 = node->latitude;
        } else {
            lon2 = node->longitude;
            lat2 = node->latitude;
        }

        wpt_count++;
        iter = iter->next;
    }

    float distance = (dist(lat1, lon1, lat2, lon2)) * 1000;

    if ((wpt_count >= 4) && (delta >= distance)) {
        return true;
    }

    return false;
}

bool isLoopTrack(const Track *tr, float delta) {
    if (tr == NULL) {
        return false;
    }
    if (delta < 0) {
        return false;
    }
    int wpt_count = 0;
    float lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;


    Node *iter = tr->segments->head;

    while (iter != NULL) {
        TrackSegment *seg_iter = (TrackSegment *)iter -> data;
        Node *wpt_node = seg_iter -> waypoints -> head;
        while (wpt_node != NULL) {
            Waypoint *node = (Waypoint *)wpt_node->data;
            if (wpt_count == 0) {
                lon1 = node->longitude;
                lat1 = node->latitude;
            } else {
                lon2 = node->longitude;
                lat2 = node->latitude;
            }

            wpt_count++;
            wpt_node = wpt_node->next;
        }
        iter = iter -> next;
    }

    float distance = (dist(lat1, lon1, lat2, lon2)) * 1000;

    if ((wpt_count >= 4) && (delta >= distance)) {
        return true;
    }

    return false;
}

void deleteList(void *data) {
    return;
}

List *getRoutesBetween(const GPXdoc *doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta) {
    if (doc == NULL) {
        return NULL;
    }
    if (delta < 0) {
        return NULL;
    }

    int counter, endpresent, num_of_between = 0;
    float lat1, lon1, lat2, lon2;

    List *rte_list = initializeList(&routeToString, &deleteList, &compareRoutes);
    Node *rte_iter = doc->routes->head;

    while (rte_iter != NULL) {
        counter = 0;
        lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;
        Route *rte_ptr = (Route *)rte_iter->data;
        Node *wpt_iter = rte_ptr->waypoints->head;
        while (wpt_iter != NULL) {
            Waypoint *wpt_ptr = (Waypoint *)wpt_iter->data;

            if (counter == 0) {
                lat1 = wpt_ptr->latitude;
                lon1 = wpt_ptr->longitude;
            } else {
                lat2 = wpt_ptr->latitude;
                lon2 = wpt_ptr->longitude;
                endpresent = 1;
            }
            counter++;
            wpt_iter = wpt_iter -> next;
        }
        if (delta >= (dist((sourceLat), (sourceLong), lat1, lon1) * 1000)) {
            if (endpresent == 0) {
                if(delta >= (dist((destLat), (destLong), lat1, lon1) * 1000)) {
                    insertBack(rte_list, rte_ptr);
                    num_of_between++;
                }
            } else {
                if(delta >= (dist((destLat), (destLong), lat2, lon2) * 1000)) {
                    insertBack(rte_list, rte_ptr);
                    num_of_between++;
                }
            }
        }
        rte_iter = rte_iter -> next;
        endpresent = 0;
    }

    if (num_of_between == 0) {
        freeList(rte_list);
        return NULL;
    }

    return rte_list;
}

List *getTracksBetween(const GPXdoc *doc, float sourceLat, float sourceLong, float destLat, float destLong, float delta) {
    if (doc == NULL) {
        return NULL;
    }
    if (delta < 0) {
        return NULL;
    }

    int counter, endpresent, num_of_between = 0;
    float lat1, lon1, lat2, lon2;

    List *trk_list = initializeList(&trackToString, &deleteList, &compareTracks);
    Node *trk_iter = doc->tracks->head;

    while (trk_iter != NULL) {
        Track *trk_ptr = (Track *)trk_iter->data;
        Node *seg_iter = trk_ptr->segments->head;

        while (seg_iter != NULL) {
            counter = 0;
            lat1 = 0, lon1 = 0, lat2 = 0, lon2 = 0;
            TrackSegment *content_segment = (TrackSegment *)seg_iter->data;
            Node *wpt_iter = content_segment->waypoints->head;

            while (wpt_iter != NULL) {
                Waypoint *wpt_ptr = (Waypoint *)wpt_iter->data;

                if (counter == 0) {
                    lat1 = wpt_ptr->latitude;
                    lon1 = wpt_ptr->longitude;
                } else {
                    lat2 = wpt_ptr->latitude;
                    lon2 = wpt_ptr->longitude;
                    endpresent = 1;
                }
                counter++;
                wpt_iter = wpt_iter -> next;

            }
            seg_iter = seg_iter->next;
        }
        if (delta >= (dist((sourceLat), (sourceLong), lat1, lon1) * 1000)) {
            if (endpresent == 0) {
                if(delta >= (dist((destLat), (destLong), lat1, lon1) * 1000)) {
                    insertBack(trk_list, trk_ptr);
                    num_of_between++;
                }
            } else {
                if(delta >= (dist((destLat), (destLong), lat2, lon2) * 1000)) {
                    insertBack(trk_list, trk_ptr);
                    num_of_between++;
                }
            }
        }
        trk_iter = trk_iter->next;
        endpresent = 0;
    }

    if (num_of_between == 0) {
        freeList(trk_list);
        return NULL;
    }

    return trk_list;
}

int routeCount(const Route *doc) {
    int i = 0;
    if (doc == NULL) {
        return 0;
    }

    Node *iter = doc -> waypoints -> head;

    while (iter !=NULL) {
        i++;
        iter = iter -> next;
    }

    return i;
}

int trackCount(const Track *doc) {
    int i = 0;
    if (doc == NULL) {
        return 0;
    }

    Node *trk_iter = doc -> segments -> head;
    while (trk_iter !=NULL) {
      TrackSegment *seg_ptr = (TrackSegment *)trk_iter -> data;
      Node *seg_iter = seg_ptr -> waypoints -> head;
      while (seg_iter != NULL) {
          i++;
          seg_iter = seg_iter -> next;
      }

      trk_iter = trk_iter -> next;
    }

    return i;
}

char *waypointToJSON(const Waypoint *wp, int ind) {
    if (wp == NULL) {
        return "{}";
    }

    int waypoint_size = strlen(wp->name) + sizeof(wp -> latitude) + sizeof(wp -> longitude) + 10000;
    char *temp = (char *)malloc(sizeof(char) * waypoint_size);

    float lon = wp -> longitude;
    float lat = wp -> latitude;

    char *name;
    if (strcmp(wp->name, "") == 0) {
        name = "None";
    } else {
        name = wp->name;
    }
    sprintf(temp, "<\"index\":\"%d\",\"longitude\":%.7f,\"latitude\":%.7f,\"name\":%s>", ind, lon, lat, name);
    int i;
    for (i = 0; temp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, temp);

    free(temp);
    return final;
}

char *routeToJSON(const Route *rt) {
    if (rt == NULL) {
        return "{}";
    }

    int route_size = strlen(rt->name) + sizeof(rt->waypoints) + sizeof(rt->otherData) + 10000;
    char *temp = (char *)malloc(sizeof(char) * route_size);

    float len = round10(getRouteLen(rt));

    char *loop;
    if (isLoopRoute(rt, 10)) {
        loop = "true";
    } else {
        loop = "false";
    }

    char *name;
    if (strcmp(rt->name, "") == 0) {
        name = "None";
    } else {
        name = rt->name;
    }

    sprintf(temp, "{\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s}", name, routeCount(rt), len, loop);
    int i;
    for (i = 0; temp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, temp);

    free(temp);
    return final;
}

char *waypointlistToJSON(const List *ls) {
    if (ls == NULL) {
        char *c = malloc(sizeof("[]"));
        return c;
    }

    char *tpr;
    char *strtmp = malloc(10000);
    strcpy(strtmp, "[");

    Node *iter = ls->head;
    int i = 0;
    while (iter != NULL) {
        Waypoint *content_route = (Waypoint *)iter->data;

        tpr = waypointToJSON(content_route, i);
        strcat(strtmp, tpr);
        free(tpr);

        iter = iter->next;
        if (iter != NULL) {
            strcat(strtmp, ",");
        }
        i++;
    }
    strcat(strtmp, "]");
    // int i;
    for (i = 0; strtmp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, strtmp);

    free(strtmp);
    return final;

}

char *routeToJSON_point(const Route *rt) {
    if (rt == NULL) {
        return "{}";
    }

    int route_size = strlen(rt->name) + sizeof(rt->waypoints) + sizeof(rt->otherData) + 10000;
    char *temp = (char *)malloc(sizeof(char) * route_size);

    float len = round10(getRouteLen(rt));

    char *loop;
    if (isLoopRoute(rt, 10)) {
        loop = "true";
    } else {
        loop = "false";
    }

    char *name;
    if (strcmp(rt->name, "") == 0) {
        name = "None";
    } else {
        name = rt->name;
    }

    char* waypointlist = waypointlistToJSON(rt -> waypoints);

    sprintf(temp, "{\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s,%s}", name, routeCount(rt), len, loop, waypointlist);
    int i;
    for (i = 0; temp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, temp);

    free(temp);
    return final;
}

char *trackToJSON(const Track *tr) {
    if (tr == NULL) {
        return "{}";
    }

    int track_size = strlen(tr->name) + sizeof(tr->segments) + sizeof(tr->otherData) + 10000;
    char *temp = (char *)malloc(sizeof(char) * track_size);

    float len = round10(getTrackLen(tr));

    char *loop;
    if (isLoopTrack(tr, 10)) {
        loop = "true";
    } else {
        loop = "false";
    }

    char *name;
    if (strcmp(tr->name, "") == 0) {
        name = "None";
    } else {
        name = tr->name;
    }

    sprintf(temp, "{\"name\":\"%s\",\"len\":%.1f,\"loop\":%s}", name, len, loop);
    int i;
    for (i = 0; temp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, temp);

    free(temp);
    return final;
}

char *trackToJSON2(const Track *tr) {
    if (tr == NULL) {
        return "{}";
    }

    int track_size = strlen(tr->name) + sizeof(tr->segments) + sizeof(tr->otherData) + 10000;
    char *temp = (char *)malloc(sizeof(char) * track_size);

    float len = round10(getTrackLen(tr));

    char *loop;
    if (isLoopTrack(tr, 10)) {
        loop = "true";
    } else {
        loop = "false";
    }

    char *name;
    if (strcmp(tr->name, "") == 0) {
        name = "None";
    } else {
        name = tr->name;
    }
    // sprintf(temp, "{\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s}", name, routeCount(rt), len, loop);

    sprintf(temp, "{\"name\":\"%s\",\"numPoints\":%d,\"len\":%.1f,\"loop\":%s}", name, trackCount(tr),len, loop);
    int i;
    for (i = 0; temp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, temp);

    free(temp);
    return final;
}

char *trackToJSON3(const Track *tr) {
    if (tr == NULL) {
        return "{}";
    }

    int track_size = strlen(tr->name) + sizeof(tr->segments) + sizeof(tr->otherData) + 10000;
    char *temp = (char *)malloc(sizeof(char) * track_size);
    char *temp2 = (char *)malloc(sizeof(char) * track_size);

    strcpy(temp, "");

    Node *trk_iter = tr -> otherData -> head;
    while (trk_iter !=NULL) {
      GPXData *data_ptr = (GPXData *)trk_iter -> data;

      sprintf(temp2, "{\"name\":\"%s\",\"value\":\"%s\"}", data_ptr -> name, data_ptr -> value);
      // printf("%s\n",temp2);

      strcat(temp, temp2);
      trk_iter = trk_iter -> next;
      if (trk_iter != NULL) {
        strcat(temp, ",");
      }
    }


    free(temp2);
    return temp;
}

char *routeToJSON3(const Route *rt) {
    if (rt == NULL) {
        return "{}";
    }

    int route_size = strlen(rt->name) + sizeof(rt->waypoints) + sizeof(rt->otherData) + 10000;
    char *temp = (char *)malloc(sizeof(char) * route_size);
    char *temp2 = (char *)malloc(sizeof(char) * route_size);

    strcpy(temp, "");

    Node *rte_iter = rt -> otherData -> head;
    while (rte_iter !=NULL) {
      GPXData *data_ptr = (GPXData *)rte_iter -> data;

      sprintf(temp2, "{\"name\":\"%s\",\"value\":\"%s\"}", data_ptr -> name, data_ptr -> value);
      // printf("%s\n",temp2);

      strcat(temp, temp2);
      rte_iter = rte_iter -> next;
      if (rte_iter != NULL) {
        strcat(temp, ",");
      }
    }


    free(temp2);
    return temp;
}

char *routeListToJSON(const List *ls) {
    if (ls == NULL) {
        char *c = malloc(sizeof("[]"));
        return c;
    }

    char *tpr;
    char *strtmp = malloc(10000);
    strcpy(strtmp, "[");

    Node *iter = ls->head;
    while (iter != NULL) {
        Route *content_route = (Route *)iter->data;

        tpr = routeToJSON(content_route);
        strcat(strtmp, tpr);
        free(tpr);

        iter = iter->next;
        if (iter != NULL) {
            strcat(strtmp, ",");
        }
    }
    strcat(strtmp, "]");
    int i;
    for (i = 0; strtmp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, strtmp);

    free(strtmp);
    return final;
}

char *routeListToJSON_point(const List *ls) {
    if (ls == NULL) {
        char *c = malloc(sizeof("[]"));
        return c;
    }

    char *tpr;
    char *strtmp = malloc(10000);
    strcpy(strtmp, "[");

    Node *iter = ls->head;
    while (iter != NULL) {
        Route *content_route = (Route *)iter->data;

        tpr = routeToJSON_point(content_route);
        strcat(strtmp, tpr);
        free(tpr);

        iter = iter->next;
        if (iter != NULL) {
            strcat(strtmp, ",");
        }
    }
    strcat(strtmp, "]");
    int i;
    for (i = 0; strtmp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, strtmp);

    free(strtmp);
    return final;
}

char *trackListToJSON(const List *ls) {
    if (ls == NULL) {
      char *c = malloc(sizeof("[]"));
      return c;
    }

    char *tpr;
    char *strtmp = malloc(10000);
    strcpy(strtmp, "[");

    Node *iter = ls -> head;
    while (iter != NULL) {
        Track *content_track = (Track *)iter->data;

        tpr = trackToJSON(content_track);
        strcat(strtmp, tpr);
        free(tpr);

        iter = iter->next;
        if (iter != NULL) {
            strcat(strtmp, ",");
        }
    }

    strcat(strtmp, "]");
    int i;
    for (i = 0; strtmp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, strtmp);

    free(strtmp);
    return final;
}

char *trackODToJSON2(const List *ls, char* route_track) {
    if (ls == NULL) {
      char *c = malloc(sizeof("[]"));
      return c;
    }

    char *tpr;
    char *strtmp = malloc(10000);
    strcpy(strtmp, "");

    Node *iter = ls -> head;
    while (iter != NULL) {
        Track *content_track = (Track *)iter->data;

        if (strcmp(content_track -> name, route_track) == 0) {
          tpr = trackToJSON3(content_track);
          strcat(strtmp, tpr);
          free(tpr);
        }

        iter = iter->next;
        if (iter != NULL) {
            strcat(strtmp, ",");
        }
    }

    int i;
    for (i = 0; strtmp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, strtmp);

    free(strtmp);
    return final;
}

char *routeODToJSON2(const List *ls, char* route_track) {
    if (ls == NULL) {
      char *c = malloc(sizeof("[]"));
      return c;
    }

    char *tpr;
    char *strtmp = malloc(10000);
    strcpy(strtmp, "");

    Node *iter = ls -> head;
    while (iter != NULL) {
        Route *content_route = (Route *)iter->data;

        if (strcmp(content_route -> name, route_track) == 0) {
          tpr = routeToJSON3(content_route);
          strcat(strtmp, tpr);
          free(tpr);
        }

        iter = iter->next;
        if (iter != NULL) {
            strcat(strtmp, ",");
        }
    }

    int i;
    for (i = 0; strtmp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, strtmp);

    free(strtmp);
    return final;
}

char *trackListToJSON2(const List *ls) {
    if (ls == NULL) {
      char *c = malloc(sizeof("[]"));
      return c;
    }

    char *tpr;
    char *strtmp = malloc(10000);
    strcpy(strtmp, "[");

    Node *iter = ls -> head;
    while (iter != NULL) {
        Track *content_track = (Track *)iter->data;

        tpr = trackToJSON2(content_track);
        strcat(strtmp, tpr);
        free(tpr);

        iter = iter->next;
        if (iter != NULL) {
            strcat(strtmp, ",");
        }
    }

    strcat(strtmp, "]");
    int i;
    for (i = 0; strtmp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, strtmp);

    free(strtmp);
    return final;
}

char *GPXtoJSON(const GPXdoc *gpx) {
    if (gpx == NULL) {
        return "{}";
    }

    int gpx_size = strlen(gpx -> creator) + sizeof(gpx -> namespace) + sizeof(gpx->waypoints) + sizeof(gpx->tracks) + sizeof(gpx->routes) + 10000;
    char *temp = (char *)malloc(sizeof(char) * gpx_size);

    sprintf(temp, "{\"version\":\"%.1f\",\"creator\":\"%s\",\"numWaypoints\":%d,\"numRoutes\":%d,\"numTracks\":%d}", gpx->version, gpx->creator, getNumWaypoints(gpx), getNumRoutes(gpx), getNumTracks(gpx));
    int i;
    for (i = 0; temp[i] != '\0'; i++) {
    }
    char *final = malloc(i + 1);
    strcpy(final, temp);

    free(temp);
    return final;
}

bool renameRoute(const List* rt, char* old_name, char* new_name) {
    if(rt == NULL) {
        return false;
    }
    if(old_name == NULL) {
        return false;
    }
    if (new_name == NULL) {
        return false;
    }

    Node *iter = rt -> head;
    while (iter != NULL) {
        Route *content_route = (Route *)iter -> data;

        if (strcmp(content_route -> name, old_name) == 0) {
            free(content_route -> name);
            int len =  strlen(new_name);
            content_route -> name = (char *)malloc(len + 1);

            strcpy(content_route -> name, new_name);
        }
        iter = iter->next;
    }
    return true;
}


void addWaypoint(Route *rt, Waypoint *pt) {
    if (rt == NULL) {
        return;
    }
    if (pt == NULL) {
        return;
    }
    if (rt -> waypoints != NULL) {
        insertBack(rt->waypoints, pt);
    }
}

void addRoute(GPXdoc *doc, Route *rt) {
    if (doc == NULL) {
        return;
    }
    if (rt == NULL) {
        return;
    }
    if (doc -> routes != NULL) {
        List *ls = doc -> routes;
        insertBack(ls, rt);
    }
}

GPXdoc* JSONtoGPX(const char* gpxString) {
    if (gpxString == NULL) {
        return NULL;
    }

    char *str1, *str2;
    char str[100];
    strcpy(str, gpxString);

    strtok((char *)str, ":");
    str1 = strtok(NULL, ",");
    if (strcmp(str1, "") == 0) {
        return NULL;
    }

    strtok(NULL, ":");
    str2 = strtok(NULL, "}");
    if (strcmp(str2, "\"\"") == 0) {
        return NULL;
    }

    GPXdoc *doc_content = malloc(sizeof(GPXdoc));

    doc_content -> creator = (char *)malloc(strlen(str2) - 1);
    str2++;
    str2[strlen(str2)-1] = 0;
    strcpy(doc_content -> creator, str2);

    doc_content->version = strtod(str1, NULL);

    int size = strlen("http://www.topografix.com/GPX/1/1") + 1;
    char *s = "http://www.topografix.com/GPX/1/1";
    int i;
    for ( i = 0; i < size; i++) {
        doc_content ->namespace[i] = s[i];
    }
    doc_content -> namespace[i] = '\0';

    List *listWaypoint = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    List *listRoute = initializeList(&routeToString, &deleteRoute, &compareRoutes);
    List *listTrack = initializeList(&trackToString, &deleteTrack, &compareTracks);

    doc_content -> waypoints = listWaypoint;
    doc_content -> routes = listRoute;
    doc_content -> tracks = listTrack;

    return doc_content;
}

Waypoint* JSONtoWaypoint(const char* name, const char* gpxString) {
    if (gpxString == NULL) {
        return NULL;
    }
    char *str1, *str2;
    char str[100];
    strcpy(str, gpxString);

    strtok((char *)str, ":");
    str1 = strtok(NULL, ",");
    if (strcmp(str1, "") == 0 && strtod(str1, NULL) == 0) {
        return NULL;
    }

    strtok(NULL, ":");
    str2 = strtok(NULL, "}");
    if (strcmp(str2, "") == 0 && strtod(str2, NULL) == 0) {
        return NULL;
    }

    Waypoint * wpt_pnt = (Waypoint *)malloc(sizeof(Waypoint));
    wpt_pnt -> name = (char *)malloc(strlen(name) + 1);
    strcpy(wpt_pnt -> name, name);
    
    List * listGPX = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    wpt_pnt -> otherData = listGPX;

    wpt_pnt -> latitude = strtod(str1, NULL);
    wpt_pnt -> longitude = strtod(str2, NULL);

    // int len =  strlen("");
    // wpt_pnt -> name = (char *)malloc(len + 1);
    // strcpy(wpt_pnt -> name, "");

    return wpt_pnt;
}

Route* JSONtoRoute(const char* gpxString) {
    if (gpxString == NULL) {
        return NULL;
    }
    char *str1;
    char str[100];
    strcpy(str, gpxString);

    strtok((char *)str, ":");
    str1 = strtok(NULL, "}");
    // if (strcmp(str1, "\"\"") == 0) {
    //     return NULL;
    // }
    str1++;
    str1[strlen(str1)-1] = 0;

    Route *rte_pnt = (Route *)malloc(sizeof(Route));
    List *ls_wpt = initializeList(&waypointToString, &deleteWaypoint, &compareWaypoints);
    rte_pnt -> waypoints = ls_wpt;

    List *ls_gpx = initializeList(&gpxDataToString, &deleteGpxData, &compareGpxData);
    rte_pnt -> otherData = ls_gpx;


    rte_pnt -> name = (char *)malloc(strlen(str1) + 1);
    strcpy(rte_pnt -> name, str1);

    return rte_pnt;
}

char *OtherDatatoJSON (const GPXdoc* gpx, char* route_track) {
  if (gpx == NULL) {
      return "[]";
  }
  int gpx_size = strlen(gpx -> creator) + sizeof(gpx -> namespace) + sizeof(gpx->waypoints) + sizeof(gpx->tracks) + sizeof(gpx->routes) + 10000;
  char *temp1 = (char *)malloc(sizeof(char) * gpx_size * 3);

  char *temp2 = (char *)malloc(sizeof(char) * gpx_size);
  temp1 = trackODToJSON2(gpx -> tracks, route_track);
  temp2 = routeODToJSON2(gpx -> routes, route_track);
  strcat(temp1, "},{");
  strcat(temp1, temp2);

  return temp1;
}

bool GPXRouteRename (const GPXdoc* gpx, char* old_name, char* new_name) {
    if (gpx == NULL) {
        return "[]";
    }

    renameRoute(gpx -> routes, old_name, new_name);
    return true;
}

char *GPXViewtoJSON (const GPXdoc* gpx) {
  if (gpx == NULL) {
      return "[]";
  }

  int gpx_size = strlen(gpx -> creator) + sizeof(gpx -> namespace) + sizeof(gpx->waypoints) + sizeof(gpx->tracks) + sizeof(gpx->routes) + 10000;
  char *temp = (char *)malloc(sizeof(char) * gpx_size * 3);
  char *temp2 = (char *)malloc(sizeof(char) * gpx_size);
  char *temp3 = (char *)malloc(sizeof(char) * gpx_size);

  temp2 = trackListToJSON2(gpx -> tracks);
  temp3 = routeListToJSON(gpx -> routes);
  // printf("%s %s\n", temp2, temp3);


  sprintf(temp, "[{\"version\":\"%.1f\",\"creator\":\"%s\",\"numWaypoints\":%d,\"numRoutes\":%d,\"numTracks\":%d}]", gpx->version, gpx->creator, getNumWaypoints(gpx), getNumRoutes(gpx), getNumTracks(gpx));
  strcat(temp, ",");
    strcat(temp, temp2);
    strcat(temp,",");
    strcat(temp, temp3);

  // free(temp);
  return temp;
}

char *GPXViewtoJSON_point (const GPXdoc* gpx) {
  if (gpx == NULL) {
      return "[]";
  }

  int gpx_size = strlen(gpx -> creator) + sizeof(gpx -> namespace) + sizeof(gpx->waypoints) + sizeof(gpx->tracks) + sizeof(gpx->routes) + 10000;
  char *temp = (char *)malloc(sizeof(char) * gpx_size * 3);
  char *temp2 = (char *)malloc(sizeof(char) * gpx_size);
  char *temp3 = (char *)malloc(sizeof(char) * gpx_size);

  temp2 = trackListToJSON2(gpx -> tracks);
  temp3 = routeListToJSON_point(gpx -> routes);
  // printf("%s %s\n", temp2, temp3);


  sprintf(temp, "[{\"version\":\"%.1f\",\"creator\":\"%s\",\"numWaypoints\":%d,\"numRoutes\":%d,\"numTracks\":%d}]", gpx->version, gpx->creator, getNumWaypoints(gpx), getNumRoutes(gpx), getNumTracks(gpx));
  strcat(temp, ",");
    strcat(temp, temp2);
    strcat(temp,",");
    strcat(temp, temp3);

  // free(temp);
  return temp;
}
